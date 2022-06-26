import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import Home from './home/home';
import About from './about/about';
import NotFound from './notFound/notFound';

function App() {
    return (
        <Router>
            <Routes>
                <Route path="/" element={<Home />} />
                <Route path="/about" element={<About />} />
                <Route path="*" element={<NotFound />} />
            </Routes>
        </Router>
    );
}

export default App;
