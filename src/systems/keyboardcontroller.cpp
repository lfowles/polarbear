#include <polarbear/systems/keyboardcontroller.hpp>

#include <functional>
#include <memory>

KeyboardControllerSystem::KeyboardControllerSystem(EventDispatch * dispatch) :
        System(dispatch)
{
    auto delegate = std::make_shared<EventDelegateMemberFunction<KeyboardControllerSystem>>(this, std::mem_fn(&KeyboardControllerSystem::HandleInput));
    dispatch->Register<InputEvent>(delegate, dispatch_id);
    accumulators.resize(2);
    system_mask.set(KeyboardControlledMovementComponent::type);
};

KeyboardControllerSystem::~KeyboardControllerSystem(void)
{
    dispatch->UnregisterAll(dispatch_id);
}

void KeyboardControllerSystem::HandleInput(EventPtr &event)
{
    auto input_event = std::dynamic_pointer_cast<InputEvent>(event);

    if (input_event->key < 128 and input_event->key >= 0)
    {
        accumulators[1].set(input_event->key);
    }
}

void KeyboardControllerSystem::update(ms time_elapsed)
{
    for (auto& entity : interesting_entities)
    {
        auto keyboard_movement = entity->Get<KeyboardControlledMovementComponent>();
        auto pos = entity->Get<PositionComponent>();

        // This should really generate movement events that get immediately dispatched using SendEvent!
        // This way AI and players can have MovableComponents that receive Move events
        auto magnitude = keyboard_movement->magnitude;//*time_elapsed.count()/1000;

        if (accumulators[1].test('w'))
        {
            pos->y -= magnitude;
        }

        if (accumulators[1].test('a'))
        {
            pos->x -= magnitude;
        }

        if (accumulators[1].test('s'))
        {
            pos->y += magnitude;
        }

        if (accumulators[1].test('d'))
        {
            pos->x += magnitude;
        }

    }

    // Move new accumulator to old accumulator spot
    if (accumulators[0].any() or accumulators[1].any())
    {
        accumulators.emplace_back();
        accumulators.erase(accumulators.begin());
    }
}