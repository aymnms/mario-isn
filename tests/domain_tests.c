/* This is a plain test binary, not an SDL app -- SDL.h is only pulled in
 * for the SDL_Rect type via domain/{grid,collision}.h. Without this define,
 * SDL_main.h #defines main to SDL_main on Windows, and linking would fail
 * with "unresolved external symbol main" unless SDL2::SDL2main is also
 * linked (see CMakeLists.txt's mario_isn target for that real app case). */
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "domain/collision.h"
#include "domain/grid.h"
#include "domain/movement.h"
#include "domain/physics.h"
#include "domain/tile.h"
#include "test_harness.h"

static void test_physics(void) {
    /* domain_jump_arc: -i^2 + 22i, roots at 0 and 22, peak 121 at i=11 */
    ASSERT_NEAR(domain_jump_arc(0), 0.0, 1e-9);
    ASSERT_NEAR(domain_jump_arc(11), 121.0, 1e-9);
    ASSERT_NEAR(domain_jump_arc(22), 0.0, 1e-9);

    /* domain_on_enemy_jump_arc: -i^2 + 15i, roots at 0 and 15, peak 56.25 at i=7.5 */
    ASSERT_NEAR(domain_on_enemy_jump_arc(0), 0.0, 1e-9);
    ASSERT_NEAR(domain_on_enemy_jump_arc(7.5), 56.25, 1e-9);
    ASSERT_NEAR(domain_on_enemy_jump_arc(15), 0.0, 1e-9);
}

static void test_grid(void) {
    SDL_Rect point;

    /* no offset: plain pixel-to-cell division by the 50px tile size */
    point.x = 125;
    point.y = 260;
    SDL_Rect cell = domain_to_grid_cell(point, 0);
    ASSERT_EQ_INT(cell.x, 2);
    ASSERT_EQ_INT(cell.y, 5);

    /* with a scroll offset added before the division (player position case) */
    point.x = 10;
    point.y = 0;
    cell = domain_to_grid_cell(point, 90);
    ASSERT_EQ_INT(cell.x, 2); /* (10+90)/50 = 2 */
    ASSERT_EQ_INT(cell.y, 0);

    /* negative pixel coordinates (integer division truncates toward zero,
     * matching the original SDL_Rect.x / 50 behavior it replaces) */
    point.x = -10;
    point.y = -60;
    cell = domain_to_grid_cell(point, 0);
    ASSERT_EQ_INT(cell.x, 0);
    ASSERT_EQ_INT(cell.y, -1);

    /* domain_clamp_to_grid: already-in-bounds cells pass through unchanged... */
    SDL_Rect in_bounds;
    in_bounds.x = 5;
    in_bounds.y = 3;
    SDL_Rect clamped = domain_clamp_to_grid(in_bounds, 10, 140);
    ASSERT_EQ_INT(clamped.x, 5);
    ASSERT_EQ_INT(clamped.y, 3);

    /* ...negative x/y clamp up to 0 (the case go()/goM()/goB() hit with
     * SDL_GetTicks()-independent negative decalage/pos_perso edge cases)... */
    SDL_Rect negative;
    negative.x = -1;
    negative.y = -1;
    clamped = domain_clamp_to_grid(negative, 10, 140);
    ASSERT_EQ_INT(clamped.x, 0);
    ASSERT_EQ_INT(clamped.y, 0);

    /* ...and a cell at or past the edge clamps down to the last valid
     * row/column -- this is the exact scenario proven reachable at max
     * scroll: (541+6700)/50 = 144, 4 columns past the grid's 0-139 range. */
    SDL_Rect past_edge;
    past_edge.x = 144;
    past_edge.y = 10;
    clamped = domain_clamp_to_grid(past_edge, 10, 140);
    ASSERT_EQ_INT(clamped.x, 139);
    ASSERT_EQ_INT(clamped.y, 9);

    /* exactly-at-the-edge (cols/rows themselves, one past the last valid
     * index) clamps the same way as further past it */
    SDL_Rect at_edge;
    at_edge.x = 140;
    at_edge.y = 10;
    clamped = domain_clamp_to_grid(at_edge, 10, 140);
    ASSERT_EQ_INT(clamped.x, 139);
    ASSERT_EQ_INT(clamped.y, 9);
}

static void test_collision(void) {
    SDL_Rect enemy;
    enemy.x = 100;
    enemy.y = 100;

    /* --- domain_contact_lateral: side touch, first x-clause (approaching
     * from the left) + y within +/-45 of the enemy --- */
    SDL_Rect player;
    player.x = 62;
    player.y = 100;
    ASSERT_TRUE(domain_contact_lateral(player, 0, enemy));

    /* second x-clause (approaching from the right) */
    player.x = 139;
    player.y = 100;
    ASSERT_TRUE(domain_contact_lateral(player, 0, enemy));

    /* far away on x: no contact */
    player.x = 500;
    player.y = 100;
    ASSERT_TRUE(!domain_contact_lateral(player, 0, enemy));

    /* x touches but y is out of range: no contact */
    player.x = 62;
    player.y = 500;
    ASSERT_TRUE(!domain_contact_lateral(player, 0, enemy));

    /* the scroll offset shifts the player's effective x */
    player.x = 62 - 30;
    player.y = 100;
    ASSERT_TRUE(domain_contact_lateral(player, 30, enemy));

    /* --- domain_lands_on_top: player's feet within +/-5px of the enemy's
     * top, while horizontally overlapping --- */
    player.x = 100;
    player.y = 50;
    ASSERT_TRUE(domain_lands_on_top(player, 0, enemy));

    /* out of x range: no landing */
    player.x = 500;
    player.y = 50;
    ASSERT_TRUE(!domain_lands_on_top(player, 0, enemy));

    /* x in range but too high above (not at landing height yet) */
    player.x = 100;
    player.y = 0;
    ASSERT_TRUE(!domain_lands_on_top(player, 0, enemy));
}

static void test_movement(void) {
    /* domain_next_direction: unchanged when clear, flipped when blocked,
     * for both directions. */
    ASSERT_EQ_INT(domain_next_direction(1, 0), 1);
    ASSERT_EQ_INT(domain_next_direction(1, 1), -1);
    ASSERT_EQ_INT(domain_next_direction(-1, 0), -1);
    ASSERT_EQ_INT(domain_next_direction(-1, 1), 1);

    /* domain_scroll_right_action: scroll whenever the player is past the
     * right-side deadzone (x>=250) AND the world hasn't hit its right edge
     * (decalage<6700) -- decalage keeps scrolling all the way up to x=500,
     * it doesn't stop just because x got big. */
    ASSERT_TRUE(domain_scroll_right_action(250, 0) == DOMAIN_SCROLL_ACTION_SCROLL_WORLD);
    ASSERT_TRUE(domain_scroll_right_action(499, 0) == DOMAIN_SCROLL_ACTION_SCROLL_WORLD);
    ASSERT_TRUE(domain_scroll_right_action(6699, 6699) == DOMAIN_SCROLL_ACTION_SCROLL_WORLD);
    /* below the deadzone, move the sprite instead regardless of decalage... */
    ASSERT_TRUE(domain_scroll_right_action(0, 0) == DOMAIN_SCROLL_ACTION_MOVE_SPRITE);
    ASSERT_TRUE(domain_scroll_right_action(249, 0) == DOMAIN_SCROLL_ACTION_MOVE_SPRITE);
    /* ...or once the world has hit its right edge, move the sprite instead
     * (until it hits its own 500px cap)... */
    ASSERT_TRUE(domain_scroll_right_action(250, 6700) == DOMAIN_SCROLL_ACTION_MOVE_SPRITE);
    ASSERT_TRUE(domain_scroll_right_action(499, 6700) == DOMAIN_SCROLL_ACTION_MOVE_SPRITE);
    /* ...and once both the world AND the sprite are capped, nothing moves. */
    ASSERT_TRUE(domain_scroll_right_action(500, 6700) == DOMAIN_SCROLL_ACTION_NONE);

    /* domain_scroll_left_action: mirror image around x<=50 / decalage>0 and
     * a 0px sprite floor instead of a 500px cap. */
    ASSERT_TRUE(domain_scroll_left_action(50, 1) == DOMAIN_SCROLL_ACTION_SCROLL_WORLD);
    ASSERT_TRUE(domain_scroll_left_action(1, 1) == DOMAIN_SCROLL_ACTION_SCROLL_WORLD);
    ASSERT_TRUE(domain_scroll_left_action(100, 0) == DOMAIN_SCROLL_ACTION_MOVE_SPRITE);
    ASSERT_TRUE(domain_scroll_left_action(51, 0) == DOMAIN_SCROLL_ACTION_MOVE_SPRITE);
    ASSERT_TRUE(domain_scroll_left_action(50, 0) == DOMAIN_SCROLL_ACTION_MOVE_SPRITE);
    ASSERT_TRUE(domain_scroll_left_action(1, 0) == DOMAIN_SCROLL_ACTION_MOVE_SPRITE);
    ASSERT_TRUE(domain_scroll_left_action(0, 0) == DOMAIN_SCROLL_ACTION_NONE);
}

static void test_tile(void) {
    /* both empty: no collision */
    ASSERT_TRUE(domain_classify_tile('0', '0') == DOMAIN_TILE_NONE);

    /* each kind, matching via either corner */
    ASSERT_TRUE(domain_classify_tile('9', '0') == DOMAIN_TILE_SPIKE);
    ASSERT_TRUE(domain_classify_tile('0', '9') == DOMAIN_TILE_SPIKE);
    ASSERT_TRUE(domain_classify_tile('2', '0') == DOMAIN_TILE_COIN);
    ASSERT_TRUE(domain_classify_tile('0', '2') == DOMAIN_TILE_COIN);
    ASSERT_TRUE(domain_classify_tile('O', '0') == DOMAIN_TILE_VICTORY_OBJECT);
    ASSERT_TRUE(domain_classify_tile('0', 'O') == DOMAIN_TILE_VICTORY_OBJECT);
    ASSERT_TRUE(domain_classify_tile('S', '0') == DOMAIN_TILE_FLAGPOLE);
    ASSERT_TRUE(domain_classify_tile('0', 'S') == DOMAIN_TILE_FLAGPOLE);

    /* any other non-'0' character: plain solid block */
    ASSERT_TRUE(domain_classify_tile('1', '0') == DOMAIN_TILE_SOLID);
    ASSERT_TRUE(domain_classify_tile('0', '1') == DOMAIN_TILE_SOLID);

    /* priority order matches the original if/else-if chain: spike beats
     * everything, coin beats victory-object and flagpole, etc. -- can't
     * actually happen with this level format (one character per cell) but
     * the original code's precedence must still be preserved exactly. */
    ASSERT_TRUE(domain_classify_tile('9', '2') == DOMAIN_TILE_SPIKE);
    ASSERT_TRUE(domain_classify_tile('2', 'O') == DOMAIN_TILE_COIN);
    ASSERT_TRUE(domain_classify_tile('O', 'S') == DOMAIN_TILE_VICTORY_OBJECT);

    /* domain_any_solid_tile: none solid */
    ASSERT_TRUE(!domain_any_solid_tile('0', '0', '0', '0'));

    /* solid at each of the 4 positions individually */
    ASSERT_TRUE(domain_any_solid_tile('1', '0', '0', '0'));
    ASSERT_TRUE(domain_any_solid_tile('0', '1', '0', '0'));
    ASSERT_TRUE(domain_any_solid_tile('0', '0', '1', '0'));
    ASSERT_TRUE(domain_any_solid_tile('0', '0', '0', '1'));

    /* a non-'1' non-'0' tile (e.g. a spike) at another corner must not mask
     * a solid '1' elsewhere -- this is exactly the case where reusing
     * domain_classify_tile() per-pair would have been wrong for goB(). */
    ASSERT_TRUE(domain_any_solid_tile('1', '9', '0', '0'));

    /* other non-'0'/non-'1' tiles alone (spike, coin) are not "solid" */
    ASSERT_TRUE(!domain_any_solid_tile('9', '2', 'O', 'S'));
}

int main(void) {
    test_physics();
    test_grid();
    test_collision();
    test_movement();
    test_tile();

    printf("%d/%d assertions passed\n", g_test_count - g_test_failures, g_test_count);
    return g_test_failures > 0 ? 1 : 0;
}
