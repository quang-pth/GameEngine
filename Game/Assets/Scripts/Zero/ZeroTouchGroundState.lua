require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroTouchGroundState = {}
setmetatable(ZeroTouchGroundState, {
    __index = ZeroState
})

ZeroTouchGroundState['Owner'] = nil
ZeroTouchGroundState['BaseFPS'] = 6
ZeroTouchGroundState['Animator'] = nil

function ZeroTouchGroundState:OnEnter(owner)
    self['Owner'] = owner
    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation('ZeroTouchGround')
    self['Animator']:SetFPS(self['BaseFPS'])
end

function ZeroTouchGroundState:OnProcessInput(inputState)

end

function ZeroTouchGroundState:OnUpdate(deltaTime)
    if self['Animator']:IsActiveAnimationFinished() then
        self['Owner']['HaveTouchedGround'] = true
        return self['Owner']['IdleState']
    end
end

function ZeroTouchGroundState:OnExit()
    
end
