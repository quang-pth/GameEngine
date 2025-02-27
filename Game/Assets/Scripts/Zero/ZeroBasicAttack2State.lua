require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroBasicAttack2State = {}
setmetatable(ZeroBasicAttack2State, {
    __index = ZeroState
})

ZeroBasicAttack2State['Owner'] = nil
ZeroBasicAttack2State['Animator'] = nil
ZeroBasicAttack2State['CommandBuffers'] = {
    FrameIndex = 0,
    Buffers = {
        -1,
        -1,
        -1,
        -1,
        -1,
    }
}
function ZeroBasicAttack2State:OnEnter(owner)
    ZeroBasicAttack2State['Owner'] = owner

    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation("ZeroBasicAttack2")
    self['Animator']:SetFPS(12)
end

function ZeroBasicAttack2State:OnProcessInput(inputState)
    local nextIndex = ZeroState:NextIndex(self['CommandBuffers']['FrameIndex'], #self['CommandBuffers']['Buffers'])
    self['CommandBuffers']['FrameIndex'] = nextIndex

    local mouseState = inputState:GetMouse()
    if mouseState:IsPressed(VIMouseButton.BUTTON_LEFT) then
        self['CommandBuffers']['Buffers'][nextIndex] = VIMouseButton.BUTTON_LEFT
    else
        self['CommandBuffers']['Buffers'][nextIndex] = -1
    end
end

function ZeroBasicAttack2State:OnUpdate(deltaTime)
    if not self['Animator']:IsActiveAnimationFinished() then
        return
    end

    local commandBuffers = self['CommandBuffers']['Buffers']
    for index = 1, #commandBuffers do
        if commandBuffers[index] == VIMouseButton.BUTTON_LEFT then
            return self['Owner']['BasicAttack3State']
        end
    end

    return self['Owner']['IdleState']
end

function ZeroBasicAttack2State:OnExit()

end

