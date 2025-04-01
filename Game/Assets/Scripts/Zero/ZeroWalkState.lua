require("Assets\\Scripts\\Zero\\ZeroState")

ZeroWalkState = {}
setmetatable(ZeroWalkState, {
    __index = ZeroState
})

ZeroWalkState['Owner'] = nil
ZeroWalkState['TriggerSlide'] = false
ZeroWalkState['CurrentVelocity'] = {x = 0.7, y = 0}
ZeroWalkState['MaxVelocity'] = {x = 1.4, y = 0}
ZeroWalkState['BaseFPS'] = 6
ZeroWalkState['CommandBuffers'] = {
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

function ZeroWalkState:OnEnter(owner)
    self['Owner'] = owner
    local animator = owner:GetAnimator()
    animator:SetActiveAnimation("ZeroWalk")
    animator:SetFPS(self['BaseFPS'])
    owner['IsReadyToSlide'] = false
    self['CurrentVelocity'] = {x = 0.7, y = 0}
end

function ZeroWalkState:OnProcessInput(inputState)
    local nextIndex = ZeroState:NextIndex(self['CommandBuffers']['FrameIndex'], #self['CommandBuffers']['Buffers'])
    self['CommandBuffers']['FrameIndex'] = nextIndex

    local owner = self['Owner']
    owner['MoveHorizontal'] = 0
    self['TriggerSlide'] = false

    local animator = owner:GetAnimator()
    local keyboardState = inputState:GetKeyboard()
    if keyboardState:IsPressed(VIKeyCode.A) then
        animator:FlipHorizontal(true);
        owner['MoveHorizontal'] = owner['MoveHorizontal'] - 1
    end
    
    if keyboardState:IsPressed(VIKeyCode.D) then
        animator:FlipHorizontal(false);
        owner['MoveHorizontal'] = owner['MoveHorizontal'] + 1
    end

    if keyboardState:IsPressed(VIKeyCode.SPACE) then
        self['CommandBuffers']['Buffers'][nextIndex] = VIMouseButton.SPACE
    else
        self['CommandBuffers']['Buffers'][nextIndex] = -1
    end

    if owner['MoveHorizontal'] == 0 then
        self['CurrentVelocity'].x = self['CurrentVelocity'].x * 0.3
    elseif self['CurrentVelocity'].x < self['MaxVelocity'].x then
        self['CurrentVelocity'].x = self['CurrentVelocity'].x + 0.1
    end

    if keyboardState:IsPressed(VIKeyCode.LEFT_SHIFT) then
        owner:ResetSlideCooldown()
        self['TriggerSlide'] = true
    end
end

function ZeroWalkState:OnUpdate(deltaTime)
    local owner = self['Owner']

    local rigidBody = owner:GetRigidBody()
    local bodyVelocityX, _ = rigidBody:GetLinearVelocity()
    local ratio = self['CurrentVelocity'].x / self['MaxVelocity'].x
    local animator = owner:GetAnimator()
    animator:SetFPS(self['BaseFPS'] * (1.0 + ratio))
    
    if self['CurrentVelocity'].x > 0.7 then
        rigidBody:ApplyForceToCenter(owner['MoveHorizontal'] * self['CurrentVelocity'].x, 0)
    end

    -- Wait for the damping to make sure that zero is completly finished the walk state before transition back to idle
    if self['CurrentVelocity'].x < 0.7 and bodyVelocityX < 0.5 then
        return owner['IdleState']
    end

    if owner['IsReadyToSlide'] and self['TriggerSlide'] then
        return owner['SlideState']
    end

    if ZeroState:CountIsPressed(self['CommandBuffers']['Buffers'], VIMouseButton.SPACE, 1) then
        local jumpState = self['Owner']['JumpState']
        jumpState:SetImpulseForward(0.15 * self['Owner']['MoveHorizontal'])
        return self['Owner']['JumpState']
    end
end

function ZeroWalkState:OnExit()
    ZeroState:ResetCommandBuffers(self['CommandBuffers'])
end

