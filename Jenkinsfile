pipeline {

    agent {
        docker {
            image 'infnpd/cmt-environment:1.0-centos7'
            args '-u 0:0'
            label 'DOCKER'
        }
    }

    stages {

        stage('Build') {

            steps {
                sh "mkdir build && cd build && cmake -D ULIB_USE_QT5:BOOL=OFF .. && make"
            }

        }

    }

}