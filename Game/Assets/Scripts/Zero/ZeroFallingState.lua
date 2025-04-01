require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroFallingState = {}
setmetatable(ZeroFallingState, {
    __index = ZeroState
})

ZeroFallingState['Owner'] = nil
ZeroFallingState['BaseFPS'] = 6
ZeroFallingState['IsOnGround'] = false

function ZeroFallingState:OnEnter(owner)
    self['Owner'] = owner
    local animator = owner:GetAnimator()
    animator:SetActiveAnimation('ZeroFalling')
    animator:SetFPS(self['BaseFPS'])
    self['IsOnGround'] = false
end

function ZeroFallingState:OnProcessInput(inputState)

end

function ZeroFallingState:OnUpdate(deltaTime)
    if self['IsOnGround'] then
        return self['Owner']['TouchGroundState']
    end
end

function ZeroFallingState:OnExit()
    
end

function ZeroFallingState:OnCollision(collision)
    self['IsOnGround'] = true
end