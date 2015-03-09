#include <polarbear/systems/cursesrender.hpp>

CursesRenderSystem::CursesRenderSystem(EventDispatch *dispatch, s render_time) :
        System(dispatch), ms_per_render(render_time), accumulated_time(0.0),
        curses(CursesSingleton::GetCurses())
{
    system_mask.set(SpriteComponent::type);
    system_mask.set(PositionComponent::type);

    // This should rather be set up at the beginning of the game
    curses->raw(true);
    curses->echo(false);
    curses->refresh();
    curses->Cursor(Swears::Curses::Visibility::Invisible);
}

void CursesRenderSystem::update(ms time_elapsed)
{
    accumulated_time += time_elapsed;
    if (accumulated_time > ms_per_render)
    {
        render(accumulated_time);
        accumulated_time = ms(0.0);// -= ms_per_render;
    }
}

void CursesRenderSystem::render(ms time_elapsed)
{
    curses->stdscr.Clear();

    // Draw gui in here? Loop over all widgets and call Draw I guess

    std::vector<std::pair<SpriteComponent*, PositionComponent*>> to_draw;
    for (auto& entity : interesting_entities)
    {
        auto pos = entity->Get<PositionComponent>();
        auto sprite = entity->Get<SpriteComponent>();

        to_draw.push_back({sprite, pos});
    }

    std::sort(to_draw.begin(), to_draw.end(),
            [](std::pair<SpriteComponent*, PositionComponent*> a, std::pair<SpriteComponent*, PositionComponent*> b)
            {
                //std::cout << b.second << " " << a.second << std::endl;
                return a.second->z < b.second->z;
            }
    );

    auto size = curses->stdscr.Size();
    for (auto& sprite_pair : to_draw)
    {
        auto& sprite = sprite_pair.first;
        auto& pos = sprite_pair.second;
        if (sprite->attr)
        {
            curses->stdscr.AttrOn(sprite->attr);
        }

        for (int y = 0; y < sprite->height and y + pos->y <= size.y; y++) {
            for (int x = 0; x < sprite->width and x + pos->x <= size.x; x++) {
                auto &c = sprite->sprite_chars[y * sprite->width + x];
                if (c != sprite->transparent_char) {
                    curses->stdscr.Write(c & 0xff, {pos->x + x, pos->y + y});
                }
            }
        }
        if (sprite->attr)
        {
            curses->stdscr.AttrOff(sprite->attr);
        }
    }
    curses->refresh();
}
