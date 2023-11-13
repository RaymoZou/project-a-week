import { Flex, Button } from "@chakra-ui/react"
import { Link } from 'react-router-dom';

const Navbar = () => {

    const logout = () => {
        localStorage.removeItem('jwt');
    }

    return (
        <nav>
            <div>
                <Flex p={2} gap={2} justifyContent="end">
                    <Button>
                        <Link to="/login">Login</Link>
                    </Button>
                    <Button>
                        <Link to="/signup">Sign Up</Link>
                    </Button>
                    <Button>
                        <Link to="/authenticated">Auth Status</Link>
                    </Button>
                    <Button onClick={logout}>
                        Logout
                    </Button>
                </Flex>
            </div>
        </nav>
    )
};

export default Navbar;