import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import Login from './Login';
import Signup from './Signup';
import Navbar from './Navbar';
import Authenticated from './Authenticated';

const App = () => {

  return (
    <Router>
      <div>
        <Navbar />

        <Routes>
          <Route path="/login" element={<Login />} />
          <Route path="/signup" element={<Signup />} />
          <Route path="/authenticated" element={<Authenticated/>} />
        </Routes>
      </div>
    </Router>
  );
};

export default App;
