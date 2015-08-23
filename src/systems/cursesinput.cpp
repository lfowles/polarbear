#include <polarbear/systems/cursesinput.hpp>
#include <ncurses.h>

void InputSystem::update(ms time_elapsed)
{
    auto events = poller->poll();
}

std::vector<Input> CursesInputPoller::poll(void)
{
    const mmask_t BUTTON_MASKS[4] = {
            BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED | BUTTON1_TRIPLE_CLICKED,
            BUTTON2_CLICKED | BUTTON2_DOUBLE_CLICKED | BUTTON2_TRIPLE_CLICKED,
            BUTTON3_CLICKED | BUTTON3_DOUBLE_CLICKED | BUTTON3_TRIPLE_CLICKED,
            BUTTON4_CLICKED | BUTTON4_DOUBLE_CLICKED | BUTTON4_TRIPLE_CLICKED
    };

    const mmask_t CLICK        = BUTTON1_CLICKED        | BUTTON2_CLICKED        | BUTTON3_CLICKED        | BUTTON4_CLICKED;
    const mmask_t DOUBLE_CLICK = BUTTON1_DOUBLE_CLICKED | BUTTON2_DOUBLE_CLICKED | BUTTON3_DOUBLE_CLICKED | BUTTON4_DOUBLE_CLICKED;
    const mmask_t TRIPLE_CLICK = BUTTON1_TRIPLE_CLICKED | BUTTON2_TRIPLE_CLICKED | BUTTON3_TRIPLE_CLICKED | BUTTON4_TRIPLE_CLICKED;

    std::vector<Input> inputs;
    while (input.has_input())
    {
        auto outgoing = Input();

        auto event = input.read();
        if (event == KEY_MOUSE)
        {
            auto outgoing_mouse = MouseInput();
            auto mouse_event = input.read_mouse();
            outgoing_mouse.x = mouse_event.x;
            outgoing_mouse.y = mouse_event.y;
            outgoing_mouse.alt = bool(mouse_event.bstate & BUTTON_ALT);
            outgoing_mouse.ctrl = bool(mouse_event.bstate & BUTTON_CTRL);
            outgoing_mouse.shift = bool(mouse_event.bstate & BUTTON_SHIFT);

            for (auto i=0; i<4; i++)
            {
                if (mouse_event.bstate & BUTTON_MASKS[i])
                {
                    outgoing_mouse.button.set(i);
                    break;
                }
            }

            if (mouse_event.bstate & CLICK)
            {
                outgoing_mouse.action = MouseInput::Action::Click;
            } else if (mouse_event.bstate & DOUBLE_CLICK) {
                outgoing_mouse.action = MouseInput::Action::DoubleClick;
            } else if (mouse_event.bstate & TRIPLE_CLICK) {
                outgoing_mouse.action = MouseInput::Action::TripleClick;
            } else {
                // Unhandled event, let's bounce
                continue;
            }
            outgoing.mouse = outgoing_mouse;
            outgoing.type = Input::Type::Mouse;
        } else {
            auto outgoing_kbd = KeyInput();
            switch(event)
            {
                case KEY_UP:
                    outgoing_kbd.arrows = KeyInput::ArrowKey::Up;
                    break;
                case KEY_DOWN:
                    outgoing_kbd.arrows = KeyInput::ArrowKey::Down;
                    break;
                case KEY_LEFT:
                    outgoing_kbd.arrows = KeyInput::ArrowKey::Left;
                    break;
                case KEY_RIGHT:
                    outgoing_kbd.arrows = KeyInput::ArrowKey::Right;
                    break;
                default:
                    outgoing_kbd.key = event & 0xFF;
                    break;
            }
            if (outgoing_kbd.key == 0x00 and outgoing_kbd.arrows == KeyInput::ArrowKey::None)
            {
                // Unhandled event, let's bounce
                continue;
            }
            outgoing.keyboard = outgoing_kbd;
            outgoing.type = Input::Type::Keyboard;
        }

        inputs.push_back(outgoing);
    }

    return inputs;
}

void CursesInputSystem::update(ms time_elapsed)
{
    while (input.has_input())
    {
        auto event = EventPtr(new InputEvent(input.read()));
        dispatch->QueueEvent(event);
    }
}