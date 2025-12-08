extends CharacterBody2D


const SPEED : int = 1600
const JUMP_VELOCITY : int = -800


func _physics_process(delta: float) -> void:


	if Input.is_action_just_pressed("ui_accept") and is_on_floor():
		velocity.y = JUMP_VELOCITY
		$JumpSound.play()


	if is_on_floor():
		var direction := Input.get_axis("ui_left", "ui_right")
		if direction:
			velocity.x = direction * SPEED / 3.5
			$AnimatedSprite2D.play("run")
			
			if direction < 0:
				$AnimatedSprite2D.flip_h = true
			else:
				$AnimatedSprite2D.flip_h = false
		else:
			velocity.x = move_toward(velocity.x, 0, SPEED)
			$AnimatedSprite2D.play("idle")

		
	else:
		velocity += get_gravity() * delta
		$AnimatedSprite2D.play("jump")

	move_and_slide()
