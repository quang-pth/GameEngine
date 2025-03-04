require("Assets\\Scripts\\Core")

Background = Background or {}

function Background:OnStart()
    local sprite = self:AddSprite()
    sprite:SetSprite("Assets/Sprite/Background/camellya-and-cat.png")
    sprite:FlipVertical(true)

    self:SetPositionX(10.0)
    self:SetPositionY(10.0)

    -- local scaleX, scaleY, _ = self:GetScale()
    self:SetScaleX(10.0)
    self:SetScaleY(15.0)
end

function Background:OnProcessInput(inputState)
    
end

function Background:OnUpdate(deltaTime)
    
end