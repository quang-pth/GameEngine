require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroBasicAttack2State = {}
setmetatable(ZeroBasicAttack2State, {
    __index = ZeroState
})

ZeroBasicAttack2State['Owner'] = nil
ZeroBasicAttack2State['Animator'] = nil

function ZeroBasicAttack2State:OnEnter(owner)
    ZeroBasicAttack2State['Owner'] = owner

    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation("ZeroBasicAttack2")
    self['Animator']:SetFPS(18)
end

function ZeroBasicAttack2State:OnProcessInput(inputState)
    ZeroState:OnProcessInput(inputState)
    local mouseState = inputState:GetMouse()
    ZeroState:SetMousePressedCommand(mouseState, VIMouseButton.BUTTON_LEFT)
end

function ZeroBasicAttack2State:OnUpdate(deltaTime)
    if not self['Animator']:IsActiveAnimationFinished() then
        return
    end

    if ZeroState:CountIsPressed(VIMouseButton.BUTTON_LEFT, 1) then
        return self['Owner']['BasicAttack3State']
    end

    return self['Owner']['IdleState']
end

function ZeroBasicAttack2State:OnExit()
    ZeroState:OnExit()
end

