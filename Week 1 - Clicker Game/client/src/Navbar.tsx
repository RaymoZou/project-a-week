import { Flex, Button } from "@chakra-ui/react"
import { Link } from 'react-router-dom';

const Navbar = () => {
    return (
        <nav>
            <Flex p={2} gap={2} justifyContent="end">
                <Button>
                    <Link to="/login">Login</Link>
                </Button>
                <Button>
                    <Link to="/signup">Sign Up</Link>
                </Button>
            </Flex>
        </nav>
    )
};

export default Navbar;