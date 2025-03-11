require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroBasicAttack1State = {}
setmetatable(ZeroBasicAttack1State, {
    __index = ZeroState
})

ZeroBasicAttack1State['Owner'] = nil
ZeroBasicAttack1State['Animator'] = nil
ZeroBasicAttack1State['CommandBuffers'] = {
    FrameIndex = 0,
    Buffers = {
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1
    }
}

function ZeroBasicAttack1State:OnEnter(owner)
    ZeroBasicAttack1State['Owner'] = owner

    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation("ZeroBasicAttack1")
    self['Animator']:SetFPS(18)
end

function ZeroBasicAttack1State:OnProcessInput(inputState)
    local nextIndex = ZeroState:NextIndex(self['CommandBuffers']['FrameIndex'], #self['CommandBuffers']['Buffers'])
    self['CommandBuffers']['FrameIndex'] = nextIndex
    
    local mouseState = inputState:GetMouse()
    if mouseState:IsPressed(VIMouseButton.BUTTON_LEFT) then
        self['CommandBuffers']['Buffers'][nextIndex] = VIMouseButton.BUTTON_LEFT
    else 
        self['CommandBuffers']['Buffers'][nextIndex] = -1
    end
end

function ZeroBasicAttack1State:OnMouseButtonPressed(button)
    -- local nextIndex = self['CommandBuffers']['FrameIndex']
    -- if button == VIMouseButton.BUTTON_LEFT then
    --     self['CommandBuffers']['Buffers'][nextIndex] = VIMouseButton.BUTTON_LEFT
    -- end
end

function ZeroBasicAttack1State:OnUpdate(deltaTime)
    local nextIndex = ZeroState:NextIndex(self['CommandBuffers']['FrameIndex'], #self['CommandBuffers']['Buffers'])
    self['CommandBuffers']['FrameIndex'] = nextIndex

    if not self['Animator']:IsActiveAnimationFinished() then
        return
    end

    if ZeroState:CountIsPressed(self['CommandBuffers']['Buffers'], VIMouseButton.BUTTON_LEFT, 1) then
        return self['Owner']['BasicAttack2State']
    end

    return self['Owner']['IdleState']
end

function ZeroBasicAttack1State:OnExit()
end

