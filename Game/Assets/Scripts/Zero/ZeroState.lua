ZeroState = {}

function ZeroState:OnEnter(owner) end

function ZeroState:OnProcessInput(inputState) end

function ZeroState:OnUpdate(deltaTime) end

function ZeroState:NextIndex(currentIndex, upperBound)
    local nextIndex = currentIndex + 1

    if nextIndex > upperBound then
        nextIndex = nextIndex - upperBound
    end

    return nextIndex
end

function ZeroState:OnKeyPressed(keyCode) end

function ZeroState:OnMouseButtonPressed(button) end

function ZeroState:CountIsPressed(commandBuffers, inputCommand, count)
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

function ZeroState:OnExit() end

function ZeroState:OnCollision(collision) end
