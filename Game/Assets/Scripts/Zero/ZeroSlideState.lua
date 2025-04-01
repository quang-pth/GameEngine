require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroSlideState = {}
setmetatable(ZeroSlideState, {
    __index = ZeroState
})

ZeroSlideState['Owner'] = nil
ZeroSlideState['Animator'] = nil
ZeroSlideState['Speed'] = 7.5
ZeroSlideState['ContinuedSlide'] = true
ZeroSlideState['CurrentVelocity'] = {x = 2.5, y = 0}
ZeroSlideState['MaxVelocity'] = {x = 2.5, y = 0}
ZeroSlideState['BaseFPS'] = 9

function ZeroSlideState:OnEnter(owner)
    self['Owner'] = owner
    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation("ZeroSlide")
    self['Animator']:SetFPS(self['BaseFPS'])
    self['CurrentVelocity'] = {x = 2.5, y = 0}
end

function ZeroSlideState:OnProcessInput(inputState)
    local owner = self['Owner']
    owner['MoveHorizontal'] = 0
    self['ContinuedSlide'] = false

    local keyboardState = inputState:GetKeyboard()
    if keyboardState:IsPressed(VIKeyCode.A) then
        self['Animator']:FlipHorizontal(true)
        owner['MoveHorizontal'] = owner['MoveHorizontal'] - 1
    elseif keyboardState:IsPressed(VIKeyCode.D) then
        self['Animator']:FlipHorizontal(false)
        owner['MoveHorizontal'] = owner['MoveHorizontal'] + 1
    end

    if owner['MoveHorizontal'] == 0 then
        self['CurrentVelocity'].x = self['CurrentVelocity'].x * 0.95
    end

    if keyboardState:IsPressed(VIKeyCode.LEFT_SHIFT) then
        self['ContinuedSlide'] = true
    end

end

function ZeroSlideState:OnUpdate(deltaTime)
    local owner = self['Owner']
    
    local rigidBody = owner:GetRigidBody()
    local bodyVelocityX, _ = rigidBody:GetLinearVelocity()
    local ratio = self['CurrentVelocity'].x / self['MaxVelocity'].x
    local animator = owner:GetAnimator()
    animator:SetFPS(self['BaseFPS'] * (1.0 + ratio))
    
    if self['CurrentVelocity'].x > 0.7 then
        rigidBody:ApplyForceToCenter(owner['MoveHorizontal'] * self['CurrentVelocity'].x, 0)
    end
    

    if not self['ContinuedSlide'] and self['CurrentVelocity'].x < 0.7 and bodyVelocityX < 0.5 then
        return owner['PrevState']
    end

    -- if not self['ContinuedSlide'] then
    --     return owner['PrevState']
    -- end

    
    if owner['MoveHorizontal'] == 0 then
        return owner['IdleState']
    end

    if self['Animator']:IsActiveAnimationFinished() then
        return owner['PrevState']
    end

    -- local x, y, _ = owner:GetPosition();

    -- owner:SetPositionX(x + owner['MoveHorizontal'] * self['Speed'] * deltaTime)
    -- owner:SetPositionY(y + owner['MoveVertical'] * self['Speed'] * deltaTime)
end

function ZeroSlideState:OnExit()
end

