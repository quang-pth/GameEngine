ZeroState = {}

ZeroState['CommandBuffers'] = {
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

function ZeroState:OnEnter(owner) end

function ZeroState:OnProcessInput(inputState)
    local nextIndex = ZeroState:NextIndex(self['CommandBuffers']['FrameIndex'], #self['CommandBuffers']['Buffers'])
    self['CommandBuffers']['FrameIndex'] = nextIndex
end

function ZeroState:OnUpdate(deltaTime) end

function ZeroState:NextIndex(currentIndex, upperBound)
    local nextIndex = currentIndex + 1

    if nextIndex > upperBound then
        nextIndex = nextIndex - upperBound
    end

    return nextIndex
end

function ZeroState:SetMousePressedCommand(mouseState, command)
    local currentIndex = self['CommandBuffers']['FrameIndex']
    if mouseState:IsPressed(command) then
        self['CommandBuffers']['Buffers'][currentIndex] = command
    else 
        self['CommandBuffers']['Buffers'][currentIndex] = -1
    end
end

function ZeroState:SetKeyboardPressedCommand(keyboardState, command)
    local currentIndex = self['CommandBuffers']['FrameIndex']
    if keyboardState:IsPressed(command) then
        self['CommandBuffers']['Buffers'][currentIndex] = command
    else 
        self['CommandBuffers']['Buffers'][currentIndex] = -1
    end
end

function ZeroState:OnKeyPressed(keyCode) end

function ZeroState:OnMouseButtonPressed(button) end

function ZeroState:CountIsPressed(inputCommand, count)
    local commandBuffers = self['CommandBuffers']['Buffers']
    local times = 0
    for i = 1, #commandBuffers do
        if commandBuffers[i] == inputCommand then
            times = times + 1
        end
    end

    return times >= count
end

function ZeroState:CountCommand(commandBuffers, inputCommand)
    local times = 0
    for i = 1, #commandBuffers do
        if commandBuffers[i] == inputCommand then
            times = times + 1
        end
    end

    return times
end

function ZeroState:ResetCommandBuffers(command)
    for i=1, #command['Buffers'] do
        command['Buffers'][i] = -1
    end
    command['FrameIndex'] = 0
end

function ZeroState:OnExit()
    self:ResetCommandBuffers(self['CommandBuffers'])
end

function ZeroState:OnCollision(collision) end
