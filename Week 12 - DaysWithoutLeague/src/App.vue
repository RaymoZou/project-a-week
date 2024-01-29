<!-- using the Options API  -->
<script lang="ts">
import axios from 'axios';
import { fromUnixTime } from 'date-fns';
import Cookie from 'js-cookie';

export default {

	data(): {
		lastGame: any,
		puuid: string,
		gameName: string,
		tagLine: string,
		apiStatus: boolean,
		riotApi: string,
	} {
		return {
			lastGame: null,
			puuid: '',
			gameName: '',
			tagLine: '',
			apiStatus: false,
			riotApi: '',
		}
	},

	computed: {
		lastPlayed() { return this.lastGame ? fromUnixTime(this.lastGame.info.gameCreation / 1000) : "NOT LOADED" }
	},

	methods: {
		async getData() {
			// TODO: fix api query by game name + tag line
			// const response = await axios.get(`https://americas.api.riotgames.com/riot/account/v1/accounts/by-riot-id/${this.gameName}/${this.tagLine}?api_key=${import.meta.env.VITE_RITO_API}`)
			const response = await axios.get(`https://americas.api.riotgames.com/lol/match/v5/matches/by-puuid/${this.puuid}/ids?start=0&count=1&api_key=${this.riotApi}`)
			const matchId = response.data
			const gameInfo = await axios.get(`https://americas.api.riotgames.com/lol/match/v5/matches/${matchId}?api_key=${this.riotApi}`)
			this.lastGame = gameInfo.data
			// console.log(gameInfo.data.info.gameCreation)
		},

		handle_puuid_submit(e: Event) {
			e.preventDefault();
			// gameName and tagLine should != null at this point
			this.getData();
		},

		async handle_api_submit(e: Event) {
			e.preventDefault();
			// check response status is === 200
			console.log(this.riotApi)
			try {
				const response = await axios.get(`https://na1.api.riotgames.com/lol/status/v4/platform-data?api_key=${this.riotApi}`)
				if (response.status === 200) {
					this.apiStatus = true;
					Cookie.set('api_key', this.riotApi)
				} else {
					console.log('nope')
				}
			} catch (err) {
				// TODO: proper error handling
				console.log(err)
			}
		},

		async is_key_valid(key: string | undefined): Promise<boolean> {
			console.log("checking")
			try {
				const res = await axios.get(`https://na1.api.riotgames.com/lol/status/v4/platform-data?api_key=${key}`)
				return res.status === 200;
			} catch (err) {
				console.log(err)
			}
			return false;
		}

	},

	mounted() {
		// check cookies for api key AND if the api key is still valid
		// TODO: this only checks if there api_key is not null, there is no check for whether or not the actual key is valid
		const key: string | undefined = Cookie.get('api_key');
		if (key !== undefined) {
			this.riotApi = key;
			this.apiStatus = true;
		}
	},

}
</script>

<template>
	<h1>Last League of Legends Game</h1>
	<p v-if="apiStatus">You are ready to make an API request!</p>
	<p v-else="apiStatus">Input your Riot API </p>
	<form v-else="apiStatus" @submit="handle_api_submit">
		<input type="text" v-model="riotApi" placeholder="RGAPI-XXXXXXXX-...">
		<button>submit</button>
	</form>
	<form v-if="apiStatus" @submit="handle_puuid_submit">
		<input type="text" v-model="puuid" placeholder="puuid" required>
		<!-- <input type="text" v-model="gameName" placeholder="gameName" required> -->
		<!-- <input type="text" v-model="tagLine" placeholder="tagLine" required> -->
		<button>submit</button>
	</form>
	<p v-if="apiStatus"><strong>Last game of League of Legends played on:</strong> {{ lastPlayed }}</p>
	<p v-if="apiStatus">{{ puuid ? puuid : "puid not loaded" }}</p>
</template>
