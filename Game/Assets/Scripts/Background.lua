require("Assets\\Scripts\\Core")

Background = Background or {}

Background['Height'] = 10.0;

function Background:OnStart()
    local sprite = self:AddSprite()
    sprite:SetSprite("Assets/Sprite/Background/camellya-and-cat.png")
    sprite:FlipVertical(true)

    self:SetPositionX(10.0)
    self:SetPositionY(20.0)

    self:SetScaleX(self['Height'] * 0.75)
    self:SetScaleY(self['Height'])
end

function Background:OnProcessInput(inputState)
    
end

function Background:OnKeyPressed(keyCode)
    
end

function Background:OnMouseButtonPressed(button)
end

function Background:OnUpdate(deltaTime)
    
end