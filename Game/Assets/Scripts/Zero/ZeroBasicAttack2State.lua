require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroBasicAttack2State = {
    __index = ZeroState
}

ZeroBasicAttack2State['Owner'] = nil
ZeroBasicAttack2State['Animator'] = nil
ZeroBasicAttack2State['TriggerBasicAttack3'] = false

function ZeroBasicAttack2State:OnEnter(owner)
    ZeroBasicAttack2State['Owner'] = owner

    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation("ZeroBasicAttack2")
    self['Animator']:SetFPS(12)
end

function ZeroBasicAttack2State:OnProcessInput(inputState)
    ZeroBasicAttack2State['TriggerBasicAttack3'] = false

    local mouseState = inputState:GetMouse()
    if not self['Animator']:IsActiveAnimationFinished() and mouseState:IsPressed(VIMouseButton.BUTTON_LEFT) then
        self['TriggerBasicAttack3'] = true
    end
end

function ZeroBasicAttack2State:OnUpdate(deltaTime)
    if not self['Animator']:IsActiveAnimationFinished() then
        return
    end

    if self['TriggerBasicAttack3'] == true then
        return self['Owner']['BasicAttack3State']
    end

    return self['Owner']['IdleState']
end

function ZeroBasicAttack2State:OnExit()

end

