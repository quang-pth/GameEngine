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

function ZeroState:OnExit() end
