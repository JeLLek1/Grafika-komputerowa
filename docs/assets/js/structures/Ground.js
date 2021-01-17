import * as THREE from 'three';

class Ground{
	constructor(scene){

		this.scene = scene;

		var material = new THREE.MeshPhongMaterial({ color: 0xffffff, specular: 0x111111});
		this.plane = new THREE.Mesh(new THREE.PlaneGeometry(1500, 1500), material);

		this.scene.add(this.plane);
		this.plane.rotation.x = - Math.PI / 2;
		this.plane.receiveShadow = true;
		this.plane.castShadow = true;
	}
}

export default Ground;