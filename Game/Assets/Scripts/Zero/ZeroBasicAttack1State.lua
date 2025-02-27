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
        -1
    }
}

function ZeroBasicAttack1State:OnEnter(owner)
    ZeroBasicAttack1State['Owner'] = owner

    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation("ZeroBasicAttack1")
    self['Animator']:SetFPS(12)
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

function ZeroBasicAttack1State:OnUpdate(deltaTime)
    if not self['Animator']:IsActiveAnimationFinished() then
        return
    end

    local commandBuffers = self['CommandBuffers']['Buffers']
    for index = 1, #commandBuffers do
        if commandBuffers[index] == VIMouseButton.BUTTON_LEFT then
            return self['Owner']['BasicAttack2State']
        end
    end

    return self['Owner']['IdleState']
end

function ZeroBasicAttack1State:OnExit()
end

