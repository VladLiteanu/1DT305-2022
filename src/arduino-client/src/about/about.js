import React from 'react';
import './about.css';
import Grid from '@material-ui/core/Grid';
import Typography from '@mui/material/Typography';
import Breadcrumbs from '@mui/material/Breadcrumbs';
import Link from '@mui/material/Link';
import HomeIcon from '@mui/icons-material/Home';
import InfoIcon from '@mui/icons-material/Info';

class about extends React.Component {

    handleClick(event) {
        console.info('You clicked a breadcrumb.');
    }

    render() {
        return (
            <Grid container spacing={1}>
                <Grid item xs={12}>
                    <div role="presentation" onClick={this.handleClick} >
                        <Breadcrumbs aria-label="breadcrumb">
                            <Typography sx={{ display: 'flex', alignItems: 'center' }}
                                color="text.primary">
                                <InfoIcon sx={{ mr: 0.5 }} fontSize="inherit" />
                                About
                            </Typography>
                            <Link
                                underline="hover"
                                sx={{ display: 'flex', alignItems: 'center' }}
                                color="#1D3557"
                                href="/"
                            >
                                <HomeIcon sx={{ mr: 0.5 }} fontSize="inherit" />
                                Home
                            </Link>
                        </Breadcrumbs>
                    </div>
                </Grid>
                <Grid item xs={12}>
                    <section className="error-container">
                        <span>Ab</span>
                        <span><span className="screen-reader-text">o</span></span>
                        <span>ut</span>
                    </section>
                    <p class="zoom-area">
                        This is the forntend for the Arduino client. Created by <a href="https://github.com/VladLiteanu">Vlad Liteanu</a> for the 1DT305 summer course 2022.
                    </p>
                    <p class="zoom-area">
                        You can find the source code of this component
                        on the following repository:
                    </p>
                    <p class="zoom-area">
                        <a href="https://github.com/VladLiteanu/1DT305-2022">Github</a>
                    </p>
                </Grid>
            </Grid>
        );
    }
}

export default about;