import * as THREE from 'three';

/**
 * Bałwan i jego animacja
**/
class SnowMan{
	constructor(param){
		this.scene = param.scene;

		this.snowMan = this.createSnowMan();
		this.snowMan.castShadow = true;
		this.snowMan.receiveShadow = true;
		this.nose = this.createNose();
		this.nose.castShadow = true;
		this.nose.receiveShadow = true;
		this.eyeLeft = this.createEye(new THREE.Vector3(-1.5, 15, 2));
		this.eyeRight = this.createEye(new THREE.Vector3(+1.5, 15, 2));


		this.group = new THREE.Group();
		this.group.add(this.snowMan);
		this.group.add(this.nose);
		this.group.add(this.eyeLeft);
		this.group.add(this.eyeRight);

		this.group.position.copy(param.pos);

		this.scene.add(this.group);

		this.animation = {
			isRunning: false,
			current: 0,
			lastUpdate: null,
		}
	}
	// tworzenie białych kulek bałwana
	createSnowMan(){
		let points = [],
			firstResolution = 30,
			firstRadius = 6,
			secondResolution = 20,
			secondRadius = 4,
			firstShift = firstRadius+secondRadius-2,
			thirdResolution = 10,
			thirdRadius = 3,
			secondShift = firstShift+thirdRadius+3;

		// pierwsza kulka
		let part = Math.PI/firstResolution;
        for (var angle = 0; angle < 9*Math.PI/10; angle+=part) {
            points.push(new THREE.Vector3(Math.sin(angle) * firstRadius, Math.cos(angle) * firstRadius, 0));
        }

        // druga kulka
		part = Math.PI/secondResolution;
        for (var angle = 1*Math.PI/10; angle < 9*Math.PI/10; angle+=part) {
            points.push(new THREE.Vector3(Math.sin(angle) * secondRadius, Math.cos(angle) * secondRadius - firstShift, 0 ));
        }

        // trzecia kulka
		part = Math.PI/thirdResolution;
        for (var angle = 1*Math.PI/10; angle <= Math.PI; angle+=part) {
            points.push(new THREE.Vector3(Math.sin(angle) * thirdRadius, Math.cos(angle) * thirdRadius - secondShift, 0));
        }

        var latheGeometry = new THREE.LatheGeometry(points, 50, 0, Math.PI*2);

        latheGeometry.rotateX(Math.PI);

		var material = new THREE.MeshPhongMaterial({
			color: 0xffffff,
			specular: 0x111111,
			side: THREE.DoubleSide,
			shadowSide: THREE.DoubleSide,
		});
		var lathe = new THREE.Mesh( latheGeometry, material );

	    return lathe;
	}

	createNose(){
		let geometry = new THREE.ConeGeometry( 1, 5, 10 );
		geometry.rotateX(Math.PI/2);
		geometry.translate(0, 13, 4);
		let material = new THREE.MeshPhongMaterial( {color: 0xf58a42, specular: 0x111111} ),
			nose = new THREE.Mesh( geometry, material );

		return nose;
	}

	createEye(pos){
		let geometry = new THREE.SphereBufferGeometry( 1, 5, 5 );
		geometry.rotateX(Math.PI/2);
		let material = new THREE.MeshPhongMaterial( {color: 0x000000, specular: 0x000000} ),
			eye = new THREE.Mesh( geometry, material );

		eye.position.x += pos.x;
		eye.position.y += pos.y;
		eye.position.z += pos.z;

		return eye;
	}
	// ustawienia początkowe animacji
	startAnimation(timestamp){
		if(this.animation.isRunning) return;

		this.animation.isRunning = true;
		this.animation.current = 0;
		this.animation.lastUpdate = timestamp;
	}
	// funkcja przejścia animacji
	easeInOutCubic(x) {
		return x < 0.5 ? 4 * x * x * x : 1 - Math.pow(-2 * x + 2, 3) / 2;
	}


	update(timestamp){
		if(!this.animation.isRunning) return;
		let frameTime = timestamp - this.animation.lastUpdate;
		this.animation.lastUpdate = timestamp;
		this.animation.current += frameTime; 
		let partAnimationTime = 500;
		// "przykucnięcie bałwana"
		if(this.animation.current < partAnimationTime){
			let part = this.animation.current/partAnimationTime;
			this.group.scale.set(1, 1- this.easeInOutCubic(part)/2 ,1);
		// powrót z przykucnięcia
		}else if(this.animation.current < partAnimationTime*2){
			let part = (this.animation.current-partAnimationTime)/partAnimationTime;
			this.group.scale.set(1, 0.5 + this.easeInOutCubic(part)/2 ,1);
		// zamknięcie oka
		}else if(this.animation.current < partAnimationTime*3){
			let part = (this.animation.current-partAnimationTime*2)/partAnimationTime;
			this.eyeRight.scale.set(1, 1- this.easeInOutCubic(part) ,1);
		// otworzenie oka
		}else if(this.animation.current < partAnimationTime*4){
			let part = (this.animation.current-partAnimationTime*3)/partAnimationTime;
			this.eyeRight.scale.set(1, 0 + this.easeInOutCubic(part) ,1);
		// przywrócenie ustawień początkowych i zakończenie animacji
		}else{
			this.group.scale.set(1, 1 ,1);
			this.eyeRight.scale.set(1, 1 ,1);
			this.animation.isRunning = false;
		}
	}
}

export default SnowMan;