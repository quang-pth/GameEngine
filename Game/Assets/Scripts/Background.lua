require("Assets\\Scripts\\Core")

Background = Background or {}

setmetatable(Background, {
    __index = VIScript
})

function Background:OnStart()
    local sprite = self:AddSprite()
    sprite:SetSprite("Assets/Sprite/Background/camellya-and-cat.png")
    sprite:FlipVertical(false)

    self:SetPositionX(10.0)
    self:SetPositionY(5.0)

    local ratio = sprite:GetWidth() / sprite:GetHeight()
    self:SetScaleX(10)
    self:SetScaleY(10 / ratio)

    local box2D = self:AddBox2D()
    box2D:SetWidth(sprite:GetWidth() * 0.0025)
    box2D:SetHeight(sprite:GetHeight() * 0.0025)
    box2D:SetFriction(0.0)
    box2D:SetDensity(10.0)
    local rigidBody = self:AddRigidBody()
    rigidBody:SetBodyType(VIPhysic.BodyType.STATIC)
end

function Background:OnProcessInput(inputState)
    
end

function Background:OnUpdate(deltaTime)
    
end

function Background:OnCollision(collision) 
    print("From background: " .. tostring(collision:GetContactCount()))
end