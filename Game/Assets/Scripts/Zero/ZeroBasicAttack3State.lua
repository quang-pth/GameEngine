require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroBasicAttack3State = {}
setmetatable(ZeroBasicAttack3State, {
    __index = ZeroState
})

ZeroBasicAttack3State['Owner'] = nil
ZeroBasicAttack3State['Animator'] = nil

function ZeroBasicAttack3State:OnEnter(owner)
    ZeroBasicAttack3State['Owner'] = owner

    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation("ZeroBasicAttack3")
    self['Animator']:SetFPS(12)
end

function ZeroBasicAttack3State:OnProcessInput(inputState)
end

function ZeroBasicAttack3State:OnUpdate(deltaTime)
    if not self['Animator']:IsActiveAnimationFinished() then
        return
    end

    return self['Owner']['IdleState']
end

function ZeroBasicAttack3State:OnExit()

end

