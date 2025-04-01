require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroState")

ZeroIdleState = {}
setmetatable(ZeroIdleState, {
    __index = ZeroState
})

ZeroIdleState['Owner'] = nil
ZeroIdleState['Animator'] = nil
ZeroIdleState['RigidBody'] = nil
ZeroIdleState['TriggerBasicAttack1'] = false
ZeroIdleState['TriggerSlide'] = false

function ZeroIdleState:OnEnter(owner)
    self['Owner'] = owner
    self['Animator'] = owner:GetAnimator()
    self['Animator']:SetActiveAnimation("ZeroIdle")
    self['Animator']:SetFPS(6)
    self['RigidBody'] = owner:GetRigidBody()
end

function ZeroIdleState:OnProcessInput(inputState)
    ZeroState:OnProcessInput(inputState)

    local owner = self['Owner']
    owner['MoveHorizontal'] = 0

    local keyboardState = inputState:GetKeyboard()
    if keyboardState:IsPressed(VIKeyCode.A) then
        self['Animator']:FlipHorizontal(true);
        owner['MoveHorizontal'] = owner['MoveHorizontal'] - 1
    end
    
    if keyboardState:IsPressed(VIKeyCode.D) then
        self['Animator']:FlipHorizontal(false);
        owner['MoveHorizontal'] = owner['MoveHorizontal'] + 1
    end

    ZeroState:SetKeyboardPressedCommand(keyboardState, VIKeyCode.SPACE)

    local mouseState = inputState:GetMouse()
    self['TriggerBasicAttack1'] = mouseState:IsPressed(VIMouseButton.BUTTON_LEFT)
    self['TriggerSlide'] = mouseState:IsPressed(VIKeyCode.LEFT_SHIFT)
end

function ZeroIdleState:OnUpdate(deltaTime)
    ZeroState:OnUpdate(deltaTime)

    local owner = self['Owner']
    if owner['MoveHorizontal'] ~= 0 then
        return owner['WalkState']
    end

    local _, velocityY = self['RigidBody']:GetLinearVelocity()
    if not owner['HaveTouchedGround'] and velocityY < 0.0 then
        print('Idle to falling')
        return self['Owner']['FallingState']
    end

    if ZeroState:CountIsPressed(VIKeyCode.SPACE, 1) then
        local jumpState = self['Owner']['JumpState']
        jumpState:SetImpulseForward(0)
        return self['Owner']['JumpState']
    end

    if self['TriggerSlide'] then
        return owner['SlideState']
    end

    if ZeroIdleState['TriggerBasicAttack1'] then
        return owner['BasicAttack1State']
    end
end

function ZeroIdleState:OnExit()
    ZeroState:OnExit()
end


