require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroBasicAttack1State = {}
setmetatable(ZeroBasicAttack1State, {
    __index = ZeroState
})

ZeroBasicAttack1State['Owner'] = nil
ZeroBasicAttack1State['Animator'] = nil

function ZeroBasicAttack1State:OnEnter(owner)
    ZeroBasicAttack1State['Owner'] = owner

    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation("ZeroBasicAttack1")
    self['Animator']:SetFPS(18)
end

function ZeroBasicAttack1State:OnProcessInput(inputState)
    ZeroState:OnProcessInput(inputState)
    local mouseState = inputState:GetMouse()
    ZeroState:SetMousePressedCommand(mouseState, VIMouseButton.BUTTON_LEFT)
end

function ZeroBasicAttack1State:OnUpdate(deltaTime)
    if not self['Animator']:IsActiveAnimationFinished() then
        return
    end

    if ZeroState:CountIsPressed(VIMouseButton.BUTTON_LEFT, 1) then
        return self['Owner']['BasicAttack2State']
    end

    return self['Owner']['IdleState']
end

function ZeroBasicAttack1State:OnExit()
    ZeroState:OnExit()
end

