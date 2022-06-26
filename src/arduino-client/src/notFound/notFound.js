import React from "react";
import './notFound.css';

// Page created by: https://www.silocreativo.com/en/creative-examples-404-error-css/

class notFound extends React.Component {
    render() {
        return (
            <>
                <section className="error-container">
                    <span>4</span>
                    <span><span className="screen-reader-text">0</span></span>
                    <span>4</span>
                </section>
                <p className="zoom-area">Page not found.</p>
                <div className="link-container">
                    <a href="/" className="more-link">Home</a>
                </div>
            </>
        );
    }
}

export default notFound;
