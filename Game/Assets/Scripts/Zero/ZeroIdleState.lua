require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroIdleState = {
    __index = ZeroState
}

ZeroIdleState['Owner'] = nil
ZeroIdleState['Animator'] = nil
ZeroIdleState['TriggerBasicAttack1'] = false

function ZeroIdleState:OnEnter(owner)
    ZeroIdleState['Owner'] = owner
    ZeroIdleState['Animator'] = owner:GetAnimator()
    ZeroIdleState['Animator']:SetActiveAnimation("ZeroIdle")
    ZeroIdleState['Animator']:SetFPS(4)
end

function ZeroIdleState:OnProcessInput(inputState)
    local owner = ZeroIdleState['Owner']
    owner['MoveHorizontal'] = 0

    ZeroIdleState['TriggerBasicAttack1'] = false

    local keyboardState = inputState:GetKeyboard()
    if keyboardState:IsPressed(VIKeyCode.A) or keyboardState:IsPressed(VIKeyCode.LEFT) then
        ZeroIdleState['Animator']:FlipHorizontal(true);
        owner['MoveHorizontal'] = owner['MoveHorizontal'] - 1
    end

    if keyboardState:IsPressed(VIKeyCode.D) or keyboardState:IsPressed(VIKeyCode.RIGHT) then
        ZeroIdleState['Animator']:FlipHorizontal(false);
        owner['MoveHorizontal'] = owner['MoveHorizontal'] + 1
    end

    local mouseState = inputState:GetMouse()
    if mouseState:IsPressed(VIMouseButton.BUTTON_LEFT) then
        self['TriggerBasicAttack1'] = true
    end
end

function ZeroIdleState:OnUpdate(deltaTime)
    local owner = ZeroIdleState['Owner']
    if owner['MoveHorizontal'] ~= 0 then
        return owner['WalkState']
    end

    if self['TriggerBasicAttack1'] then
        return owner['BasicAttack1State']
    end
end

function ZeroIdleState:OnExit()

end

