require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroSlideState = {}
setmetatable(ZeroSlideState, {
    __index = ZeroState
})

ZeroSlideState['Owner'] = nil
ZeroSlideState['Animator'] = nil
ZeroSlideState['Speed'] = 450
ZeroSlideState['ContinuedSlide'] = true

function ZeroSlideState:OnEnter(owner)
    self['Owner'] = owner
    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation("ZeroSlide")
    self['Animator']:SetFPS(9)
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

    if keyboardState:IsPressed(VIKeyCode.LEFT_SHIFT) then
        self['ContinuedSlide'] = true
    end

end

function ZeroSlideState:OnUpdate(deltaTime)
    local owner = self['Owner']
    
    if not self['ContinuedSlide'] then
        return owner['PrevState']
    end

    
    if owner['MoveHorizontal'] == 0 then
        return owner['IdleState']
    end

    if self['Animator']:IsActiveAnimationFinished() then
        return owner['PrevState']
    end

    local x, y, _ = owner:GetPosition();

    owner:SetPositionX(x + owner['MoveHorizontal'] * self['Speed'] * deltaTime)
    owner:SetPositionY(y + owner['MoveVertical'] * self['Speed'] * deltaTime)
end

function ZeroSlideState:OnExit()
end

