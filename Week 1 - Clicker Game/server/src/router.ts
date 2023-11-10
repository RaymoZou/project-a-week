import express from 'express';
var router = express.Router();

router.get('/', (req, res) => {
    res.json('welcome to the api router');
});

// module.exports = router;
// export default router;
export { router };