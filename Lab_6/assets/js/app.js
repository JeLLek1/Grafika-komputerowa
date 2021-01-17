/**
 * Autor: Maciej Bronikowski 248838
 * Opis funkcji aplickacji:
 *    - za pomocą lewego przycisku myszy można poruszać kamerą (kamera nie zejdzie poniżej podłoża)
 *    - po kliknięciu w szklaną kulę, wykona się animacja bałwana
**/

import * as THREE from 'three';
import Ground from './structures/Ground';
import SnowBall from './structures/SnowBall';
import Camera from './view/Camera';
import Light from './view/Light';

import '../scss/app.scss'

/**
 * Główna klasa aplikacji
**/
class App{
	constructor(){
		this.renderArea = document.querySelector(`#render`);
		this.init();

		requestAnimationFrame(this.render.bind(this));
	}

	// inicjalizacja sceny
	init(){
		this.scene = new THREE.Scene();
		this.renderer = new THREE.WebGLRenderer();
		this.renderer.shadowMap.enabled = true;
		this.renderer.shadowMap.type = THREE.PCFShadowMap;

		this.renderer.setSize( this.renderArea.clientWidth,this.renderArea.clientHeight );
		this.renderArea.appendChild( this.renderer.domElement );

		this.camera = new Camera({scene: this.scene, renderer: this.renderer, renderArea: this.renderArea});
		this.light = new Light({scene: this.scene, renderer: this.renderer});

		this.ground = new Ground(this.scene);
		this.snowBall = new SnowBall(this.scene, this.renderArea);

	}

	// metoda renderująca
	render(timestamp){
		requestAnimationFrame(this.render.bind(this));

		let reyCaster = this.camera.getReycasted();

		this.light.update(timestamp);
		this.snowBall.update(timestamp, reyCaster);
		this.camera.update();

		this.renderer.render( this.scene, this.camera.getCamera() );
	}
}

(function() {
	var app = new App();
})();