import './styles.css'
import { Button, Flex, FormControl, FormLabel, Input } from '@chakra-ui/react';
import { useState } from 'react';

function App() {

  const [formData, setFormData] = useState({
    username: '',
    password: ''
  });

  const submitForm = () => console.log('clicked!');

  const handleInputChange = (e) => {
      
  }

  return (
    // <Flex bg='tomato' h='100vh' justify='center' align='center'>
    //   <h1>Welcome to Clicker Game!</h1>
    //   <FormControl>
    //     <FormLabel>Email address</FormLabel>
    //     <Input type='email' />
    //     <FormHelperText>We'll never share your email.</FormHelperText>
    //   </FormControl>
    // </Flex>
    <Flex h='100vh' justify='center' align='center' direction='column'>
      {/* <Button onClick={click}>Click Me</Button> */}
      <form action="">
        <FormControl w='max-content'>
          <FormLabel>Username</FormLabel>
          <Input type='email' autoComplete='username' />
        </FormControl>
        <FormControl w='max-content'>
          <FormLabel>Password</FormLabel>
          <Input type='password' autoComplete='current-password' />
        </FormControl>
        <Button>Submit</Button>
      </form>
    </Flex>
  )
}

export default App
