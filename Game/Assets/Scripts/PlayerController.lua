require("Assets\\Scripts\\Core")

PlayerController = PlayerController or {}

PlayerController['MoveHorizontal'] = 0

function PlayerController:OnProcessInput(keyboardState)
    PlayerController['MoveHorizontal'] = 0

    local animator = self:GetAnimator()
    if keyboardState:IsPressed(VIKeyCode.A) or keyboardState:IsPressed(VIKeyCode.LEFT) then
        animator:FlipX(true);
        PlayerController['MoveHorizontal'] = PlayerController['MoveHorizontal'] + 1
    end
end

function PlayerController:OnUpdate(deltaTime)
    --print(deltaTime)
end
