import mongoose, { Schema } from 'mongoose';

const userSchema = new Schema({
    username: { type: String, required: true, unique: true },
    hash: { type: String, required: true }
});

const User = mongoose.model('user', userSchema);

export { User }