import * as THREE from 'three';
import SnowMan from './SnowMan';

/**
 * Kula śnieżna i animacja
**/
class SnowBall{
	constructor(scene, renderArea){
		this.texUri = 'assets/img/';
		this.renderArea = renderArea;
		this.texUrls = [
		`${this.texUri}px.jpg`,`${this.texUri}nx.jpg`,
		`${this.texUri}py.jpg`,`${this.texUri}ny.jpg`,
		`${this.texUri}pz.jpg`,`${this.texUri}nz.jpg`];

		this.ballRadius = 20;
		this.groundTheta = 1*Math.PI/3;
		this.ballPos = 39;
		this.scene = scene;

		this.basis = this.createBasis();
		this.basis.castShadow = true;
		this.basis.receiveShadow = true;
		this.ball = this.createBall()
		this.ball.castShadow = true;
		this.ball.receiveShadow = true;
		this.bottomGround = this.createBottomGround();
		this.bottomGround.castShadow = true;
		this.bottomGround.receiveShadow = true;
		this.ground = this.createGround();
		this.ground.castShadow = true;
		this.ground.receiveShadow = true;

		this.snow = this.createSnow();

		this.group = new THREE.Group();
		this.group.add(this.basis);
		this.group.add(this.ball);
		this.group.add(this.bottomGround);
		this.group.add(this.ground);
		this.group.add(this.snow);

		this.scene.add(this.group);

		this.snowMan = new SnowMan({
			scene: this.scene,
			pos: new THREE.Vector3(0,this.ground.geometry.groundPosX,0)
		});
	}
	// podstawa na kulę (Czarna)
	createBasis(){
        var points = [];
        var height = 1;
        var count = 30;
        for (var i = 0; i < count; i++) {
            points.push( new THREE.Vector2( (Math.sin( i * 0.2 ) * 10 + 5)*height, ( ( i - 5 ) * 2 )*height ));
        }

        var latheGeometry = new THREE.LatheGeometry(points, 50, 0, 2 * Math.PI);
		var material = new THREE.MeshPhongMaterial({
			color: 0x000000,
			specular: 0x111111,
			side: THREE.DoubleSide,
			shadowSide: THREE.DoubleSide,
		});
		var lathe = new THREE.Mesh( latheGeometry, material );
        lathe.rotation.x = Math.PI;
        lathe.position.y = 10;
	    return lathe;
	}
	// przeźroczysta kula
	createBall(){
		let textureCube = new THREE.CubeTextureLoader().load(this.texUrls);
		textureCube.format = THREE.RGBFormat;
		textureCube.mapping = THREE.CubeReflectionMapping;
		var material = new THREE.MeshPhongMaterial({
		    shininess: 1,
		    emissiveIntensity: 0,
		    color: 0xffffff,
		    specular: 0x222222,
		    transparent: true,
		    blending: THREE.AdditiveBlending,
		    depthWrite: false,
  			envMap: textureCube
		});
		let geometry = new THREE.SphereGeometry(this.ballRadius,  16, 16),
			ball = new THREE.Mesh(geometry, material);
		ball.position.y = this.ballPos;
		return ball;
	}
	// dolna część podstawy (część sfery)
	createBottomGround(){
        var sphereGeometry = new THREE.SphereBufferGeometry( this.ballRadius-1, 26, 26, 0, Math.PI*2, 0, this.groundTheta );
		var material = new THREE.MeshPhongMaterial({
			color: 0xffffff,
			specular: 0x111111,
		});
		var spherePart = new THREE.Mesh( sphereGeometry, material );
        spherePart.position.y = this.ballPos;
        spherePart.rotation.x = Math.PI;
		return spherePart;
	}
	// płaszczyzna podstawy bałwana
	createGround(){
		var groundRadius = (this.ballRadius-1)*Math.cos(this.groundTheta/2);
		var geometry = new THREE.PlaneGeometry( groundRadius*2, groundRadius*2, 50 , 50);
		geometry.radius = groundRadius;

		geometry.rotateX(-Math.PI * 0.5);
		geometry.groundPosX = this.ballPos+(this.ballRadius-1)*Math.sin(this.groundTheta/2)-this.ballRadius + 1;
		geometry.translate(0, geometry.groundPosX, 0);
		geometry.vertices.forEach(v => {
		  v.init = new THREE.Vector3().copy(v);
		  v.amplitude = THREE.Math.randFloatSpread(1);
		  v.start = THREE.Math.randFloat(0, Math.PI);

		  v.move = v.x*v.x + v.z*v.z < Math.pow(geometry.radius - 1, 2);
		});
		var ground = new THREE.Mesh( geometry, this.getClipSphereMaterial({
			radius: this.ballRadius - 1,
			spherePos: new THREE.Vector3(0,this.ballPos,0),
			color: 0xffffff,
			specular: 0x111111,
		}));
		return ground;
	}
	// cząsteczki śniegu
	createSnow(){
		let count = 1800,
			geometry = new THREE.Geometry(),
	    	pMaterial = new THREE.PointsMaterial({
		      	color: 0xffffff,
		      	size: 0.2
		    });

		    geometry.posX = 0;
		    geometry.posY = this.ballPos;
		    geometry.posZ = 0;
		    geometry.radius = this.ballRadius-2;

		for (var i = 0; i < count; i++) {
			geometry.vertices.push(this.randomSnowPosition(geometry));
		}
		return new THREE.Points(geometry, pMaterial);
	}
	// losowanie pozycji cząsteczki śniegu tak aby znajdowała się w kuli
	randomSnowPosition(geometry){
		let theta = Math.random()*Math.PI * 2,
			v = Math.random(),
			phi = Math.acos((2*v)-1),
			radius = Math.pow(Math.random(0,1), 1/3)*geometry.radius;

		let pX = radius*Math.sin(phi)*Math.cos(theta)+geometry.posX,
			pY = radius*Math.sin(phi)*Math.sin(theta)+geometry.posY,
			pZ = radius*Math.cos(phi)+geometry.posZ;

		let vector = new THREE.Vector3(pX, pY, pZ);
		vector.velocity = new THREE.Vector3(0, 0, 0);
		return vector;
	}
	// aktualizacjia podłoża bałwana (delikatne fale)
	updateGround(progress){
		let geometry = this.ground.geometry;
		geometry.vertices.forEach(v => {
			if(v.move)
		    	v.y = v.init.y + Math.sin(progress * 2*Math.PI + v.start ) * v.amplitude;
		});
		geometry.verticesNeedUpdate = true;
		geometry.computeVertexNormals();
	}
	// aktualizacja cząsteczek śniegu (wspólna rotacja, losowe przyspieszenie i przemieszczenie)
	updateSnow(){
		let geometry = this.snow.geometry;

		let i = 0;
		this.snow.rotation.y += 0.005;
		geometry.vertices.forEach(v => {
			
			v.velocity.y -= Math.random()*0.001;
			v.add(v.velocity);
			if(Math.pow(v.x-geometry.posX,2)+Math.pow(v.y-geometry.posY,2)+Math.pow(v.z-geometry.posZ,2)>geometry.radius*geometry.radius){
				let newPos = this.randomSnowPosition(geometry);
				v.x = newPos.x;
				v.y = newPos.y;
				v.z = newPos.z;
				v.velocity = newPos.velocity;
			}
		});

		geometry.verticesNeedUpdate = true;
	}

	update(timestamp, reyCaster){
		var progress = (timestamp * 0.0001) % 1;

		let intersects = reyCaster.intersects.intersectObjects(this.group.children);
		if(intersects.length > 0){
			let selected = intersects[ 0 ].object;
			if(selected===this.ball){
				this.renderArea.style.cursor = 'pointer';
				if(reyCaster.mouse.wasPressed)
					this.snowMan.startAnimation(timestamp);
			}else{
				this.renderArea.style.cursor = 'auto';
			}
		}else{
			this.renderArea.style.cursor = 'auto';
		}


		this.updateGround(progress);
		this.updateSnow();
		this.snowMan.update(timestamp);
	}
	// tworzenie materiału z shaderem wycinającym kształ kuli w obiekcie
	getClipSphereMaterial(params){

	    let phong = new THREE.ShaderMaterial({
		    uniforms: THREE.UniformsUtils.merge([THREE.ShaderLib.phong.uniforms, {
		        clippingSphere: {
		          	value: new THREE.Vector4()
		        },
		    }]),
		    vertexShader: document.querySelector("#cliped-vertex").textContent,
		    fragmentShader: document.querySelector("#cliped-fragment").textContent,
		    lights: true,
	    });
	    phong.uniforms.clippingSphere.value.set(params.spherePos.x, params.spherePos.y, params.spherePos.z, params.radius);
		phong.uniforms.diffuse.value.setHex ( params.color );
		phong.uniforms.specular.value.setHex ( params.specular );
	    return phong;
	}
}

export default SnowBall;