import express from 'express';
var router = express.Router();

router.get('/', (req, res) => {
    res.json({message: 'you are authenticated'});
});

export { router };