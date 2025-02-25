require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroBasicAttack1State = {
    __index = ZeroState
}

ZeroBasicAttack1State['Owner'] = nil
ZeroBasicAttack1State['Animator'] = nil
ZeroBasicAttack1State['TriggerBasicAttack2'] = false

function ZeroBasicAttack1State:OnEnter(owner)
    ZeroBasicAttack1State['Owner'] = owner

    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation("ZeroBasicAttack1")
    self['Animator']:SetFPS(12)
end

function ZeroBasicAttack1State:OnProcessInput(inputState)
    ZeroBasicAttack1State['TriggerBasicAttack2'] = false

    local mouseState = inputState:GetMouse()
    if not self['Animator']:IsActiveAnimationFinished() and mouseState:IsPressed(VIMouseButton.BUTTON_LEFT) then
        self['TriggerBasicAttack2'] = true
    end
end

function ZeroBasicAttack1State:OnUpdate(deltaTime)
    if not self['Animator']:IsActiveAnimationFinished() then
        return
    end

    if self['TriggerBasicAttack2'] then
        return self['Owner']['BasicAttack2State']
    end

    return self['Owner']['IdleState']
end

function ZeroBasicAttack1State:OnExit()
end

