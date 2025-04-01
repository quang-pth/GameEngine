require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroJumpState = {}
setmetatable(ZeroJumpState, {
    __index = ZeroState
})

ZeroJumpState['Owner'] = nil
ZeroJumpState['BaseFPS'] = 6
ZeroJumpState['RigidBody'] = nil
ZeroJumpState['JumpForce'] = 0.85
ZeroJumpState['ForwardImpulse'] = 0

function ZeroJumpState:OnEnter(owner)
    self['Owner'] = owner 
    local animator = owner:GetAnimator()
    animator:SetActiveAnimation("ZeroJump")
    animator:SetFPS(self['BaseFPS'])
    self['RigidBody'] = owner:GetRigidBody()
    self['RigidBody']:ApplyImpulseToCenter(self['ForwardImpulse'], self['JumpForce'])
end

function ZeroJumpState:OnProcessInput(inputState)
    
end

function ZeroJumpState:OnUpdate(deltaTime)
    local _, velocityY = self['RigidBody']:GetLinearVelocity()

    if velocityY <= 0 then
        return self['Owner']['FallingState']
    end
end

function ZeroJumpState:OnExit()
    
end

function ZeroJumpState:SetImpulseForward(force)
    self['ForwardImpulse'] = force
end