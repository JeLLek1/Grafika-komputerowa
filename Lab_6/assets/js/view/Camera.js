import * as THREE from 'three';

/**
 * Kamera i interakcja
**/
class Camera{
	constructor(data){
		this.cameraRadius = 80;
		this.moveStep = 2;

		this.scene = data.scene;
		this.renderer = data.renderer;
		this.renderArea = data.renderArea;

		this.camera = new THREE.PerspectiveCamera( 75, this.renderArea.clientWidth / this.renderArea.clientHeight, 0.1, 1000 );
		
		this.camPos = {a: 1, b: 0.8};
		this.camCenter = new THREE.Vector3(0, 39, 0);

		this.mouse = {
			pos: new THREE.Vector2(),
			wasPressed: false
		}
		this.rayCaster = new THREE.Raycaster();

		this.update();
		this.initEvents();
	}

	initEvents(){
		// zmiana wielkości okna renderującego w zależności od wielkości kontenera głównego
		window.addEventListener( 'resize', ()=>{ this.onViewResize() }, false);
		window.addEventListener( 'mousemove', (e)=>{ this.onMouseMove(e) });
		window.addEventListener( 'mousedown', (e)=>{ this.onMouseDown(e) });
	}

	onMouseDown(e){
		this.mouse.wasPressed=true;
	}

	onViewResize(e){
		this.camera.aspect = this.renderArea.clientWidth / this.renderArea.clientHeight;
		this.camera.updateProjectionMatrix();
		this.renderer.setSize( this.renderArea.clientWidth, this.renderArea.clientHeight );
	}
	// obsługa poruszania się myszy
	onMouseMove(e){
		let temp = {
			x: ( event.clientX / window.innerWidth ) * 2 - 1,
			y: - ( event.clientY / window.innerHeight ) * 2 + 1,
		};
		if(e.buttons === 1){
			var moveX = temp.x - this.mouse.pos.x;
			var moveY = temp.y - this.mouse.pos.y;
			
			this.camPos.a += moveX*this.moveStep;
			this.camPos.b -= moveY*this.moveStep;
			if(this.camPos.a > Math.PI*2 || this.camPos.a < 0)
				this.camPos.a -= Math.floor(this.camPos.a/(Math.PI*2))*Math.PI*2;

			if(this.camPos.b < 0.1) this.camPos.b = 0.1;
			if(this.camPos.b > Math.PI / 2) this.camPos.b = Math.PI / 2;
		}

		this.mouse.pos.x = temp.x;
		this.mouse.pos.y = temp.y;
	}
	// pobranie elementów wskazywanych przez kursor
	getReycasted(){
		this.rayCaster.setFromCamera( this.mouse.pos, this.camera );
		return {
			intersects: this.rayCaster,
			mouse: this.mouse,
		}
	}

	getCamera(){
		return this.camera;
	}

	update(){
		this.camera.position.x = this.cameraRadius*Math.cos(this.camPos.a)*Math.cos(this.camPos.b);
		this.camera.position.y = this.cameraRadius*Math.sin(this.camPos.b);
		this.camera.position.z = this.cameraRadius*Math.sin(this.camPos.a)*Math.cos(this.camPos.b);
		this.camera.lookAt(this.camCenter);
		this.mouse.wasPressed = false;
	}
}

export default Camera;