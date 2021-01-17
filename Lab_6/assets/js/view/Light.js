import * as THREE from 'three';

/**
 * Światła
**/
class Light{
	constructor(data){
		this.scene = data.scene;
		this.renderer = data.renderer;

		this.directionalRadius = 1500;

		this.scene.fog = new THREE.Fog(0x000000, 70, 500);

		// światło otoczenia
		this.scene.add( new THREE.AmbientLight(0x555555));
		// światło kierunkowe
		this.directional = new THREE.DirectionalLight( 0xffffff, 0.4 );
		this.directional.position.set(1, 1, 1);
		this.directional.castShadow = true;
		this.directional.shadow.mapSize.width = 2048;
		this.directional.shadow.mapSize.height = 2048;
		let d = 100;
		this.directional.shadow.camera.left = - d;
		this.directional.shadow.camera.right = d;
		this.directional.shadow.camera.top = d;
		this.directional.shadow.camera.bottom = - d;
		this.directional.shadow.radius = 40;
		this.directional.shadow.camera.near  = 0.1;
		this.directional.shadow.camera.far  = 5000;
		this.scene.add(this.directional);

		this.setBackground();
	}

	// zamiana modelu barw hsv na rgb
	HSVtoRGB(h, s, v) {
	    var r, g, b, i, f, p, q, t;
	    if (arguments.length === 1) {
	        s = h.s, v = h.v, h = h.h;
	    }
	    i = Math.floor(h * 6);
	    f = h * 6 - i;
	    p = v * (1 - s);
	    q = v * (1 - f * s);
	    t = v * (1 - (1 - f) * s);
	    switch (i % 6) {
	        case 0: r = v, g = t, b = p; break;
	        case 1: r = q, g = v, b = p; break;
	        case 2: r = p, g = v, b = t; break;
	        case 3: r = p, g = q, b = v; break;
	        case 4: r = t, g = p, b = v; break;
	        case 5: r = v, g = p, b = q; break;
	    }
	    return (Math.round(r * 255) << 16) + (Math.round(g * 255) << 8) + Math.round(b * 255) ;
	}

	// zmiana tła (przyciemnianie gdy światło kierunkowe jest schowane pod płaszczyzną)
	setBackground(progress = 0){
		if(progress > 0.5){
			this.scene.fog.color = new THREE.Color(this.HSVtoRGB(0.6,0.5,0.25));
		}
		else if(progress > 0.25){
			this.scene.fog.color = new THREE.Color(this.HSVtoRGB(0.6,0.5,1-(progress-0.25)*3));
		}
		else{
			this.scene.fog.color = new THREE.Color(this.HSVtoRGB(0.6,0.5,0.25+progress*3));
		}


		this.renderer.setClearColor(this.scene.fog.color);
	}
	// zmiana kąta świecenia światła kierunkowego
	setDirectional(progress = 0){
		let a = 0;
		let b = progress*Math.PI*2;

		this.directional.position.x =this.directionalRadius* Math.cos(a)*Math.cos(b);
		this.directional.position.y =this.directionalRadius* Math.sin(b);
		this.directional.position.z =this.directionalRadius* Math.sin(a)*Math.cos(b);
	}

	update(timestamp){
		var progress = (timestamp * 0.00005) % 1;
		this.setBackground(progress);
		this.setDirectional(progress);
	}
}

export default Light;