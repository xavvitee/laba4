pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                git url: 'https://github.com/xavvitee/prct4.git', credentialsId: 'access_for_jenkins'
            }
        }
        
        stage('Build') {
            steps {
                script {
                    try {
                        bat "C:/Users/Валерія/Downloads/laba4/vs_mkr_test1/test_repos.sln /p:Configuration=Debug /p:Platform=x64 /m"
                    } catch (err) {
                        echo "Build failed: ${err}"
                        error "Stopping pipeline due to build failure"
                    }

                }
            }
        }
        
        stage('Test') {
            steps {
                script {
                    try {
                        bat '"C:\\Users\\User\\source\\repos\\SP_task4\\SP_task4\\x64\\Debug\\SP_task4.exe"'
                    } catch (Exception e) {
                        echo "Test error: ${e.message}"
                        currentBuild.result = 'FAILURE'
                        error("Pipeline stopped due to test execution failure.")
                    }
                }
            }
        }
    }
    
    post {
        always {
            cleanWs()
        }
        
        failure {
            echo "Pipeline failed. Check logs to fix the issues."
        }
        
        success {
            echo "Pipeline completed successfully!"
        }
    }
}