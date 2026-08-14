/* This is a plain test binary, not an SDL app -- SDL.h is only pulled in
 * for the SDL_Rect type via domain/{grid,collision}.h. Without this define,
 * SDL_main.h #defines main to SDL_main on Windows, and linking would fail
 * with "unresolved external symbol main" unless SDL2::SDL2main is also
 * linked (see CMakeLists.txt's mario_isn target for that real app case). */
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "domain/collision.h"
#include "domain/grid.h"
#include "domain/physics.h"
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

int main(void) {
    test_physics();
    test_grid();
    test_collision();

    printf("%d/%d assertions passed\n", g_test_count - g_test_failures, g_test_count);
    return g_test_failures > 0 ? 1 : 0;
}
