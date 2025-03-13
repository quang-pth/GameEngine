require("Assets\\Scripts\\Core")

Background = Background or {}

function Background:OnStart()
    local sprite = self:AddSprite()
    sprite:SetSprite("Assets/Sprite/Background/camellya-and-cat.png")
    sprite:FlipVertical(true)

    self:SetPositionX(10.0)
    self:SetPositionY(15.0)

    local ratio = sprite:GetWidth() / sprite:GetHeight()
    self:SetScaleX(9)
    self:SetScaleY(9 / ratio)

    local box2D = self:AddBox2D()
    box2D:SetWidth(sprite:GetWidth() * 0.001)
    box2D:SetHeight(sprite:GetHeight() * 0.001)
    local rigidBody = self:AddRigidBody()
    rigidBody:SetBodyType(VIPhysic.BodyType.STATIC)
end

function Background:OnProcessInput(inputState)
    
end

function Background:OnKeyPressed(keyCode)
    
end

function Background:OnMouseButtonPressed(button)
end

function Background:OnUpdate(deltaTime)
    
end