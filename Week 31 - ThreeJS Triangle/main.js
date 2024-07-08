import * as THREE from 'three';

const canvas = document.getElementById("canvas");
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;
const renderer = new THREE.WebGLRenderer({ antialias: true, canvas });
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, 2, 0.1, 5);
camera.position.z = 3;
const geometry = new THREE.BoxGeometry(1, 1, 1);
const material = new THREE.MeshBasicMaterial({ color: 0xff0000 });
const cube = new THREE.Mesh(geometry, material);

scene.add(cube)

function main() {
    renderer.render(scene, camera);
    console.log("calling main");
};

main();
