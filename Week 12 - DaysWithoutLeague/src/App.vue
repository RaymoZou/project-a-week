<!-- using the Options API  -->
<script>
import axios from 'axios';

export default {

	data() {
		return {
			games: null
		}
	},

	computed: {
		numGames() {
			return this.data ? this.data.data.length : "not loaded";
		}
	},

	methods: {
		async getData() {
			this.games = await axios.get(`https://americas.api.riotgames.com/lol/match/v5/matches/by-puuid/${import.met.env.PUUID}/ids?start=0&count=20&api_key=${import.meta.env.VITE_RITO_API}`)
		}
	},

	mounted() {
		// console.log(import.meta.env.VITE_RITO_API)
		this.getData()
		console.log("mounted")
	},
}
</script>

<template>
	<h1>Games</h1>
	<li v-for="game in games.data">
		{{ game }}
	</li>
</template>
