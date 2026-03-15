#include "Tasker.h"

namespace
{
    /*
    *   Tasker private variables
    */

    TaskHandle_t musicTaskHandle = NULL;

    const UBaseType_t mainTaskPriority = 2;
    const UBaseType_t playSongTaskPriority = 1;
    const UBaseType_t musicCtrlTaskPriority = 1;
    const UBaseType_t readBttryVoltageTaskPriority = 1;

    /*
    *   Tasker private functions
    */
    void createPlaySongTask()
    {
        xTaskCreatePinnedToCore(
            HrdwrController::playSongTask, // Task function
            "playSongTask", // Task name
            2048, // Stack size
            NULL, // Parameters
            playSongTaskPriority, // Priority
            &musicTaskHandle, // Task handle
            1 // Core ID
        );
    }

    void createMusicCtrlTask()
    {
        xTaskCreatePinnedToCore(
            HrdwrController::musicCtrlTask, // Task function
            "musicCtrlTask", // Task name
            1024, // Stack size
            NULL, // Parameters
            musicCtrlTaskPriority, // Priority
            NULL, // Task handle
            1 // Core ID
        );
    }

    void createBttryReadTask()
    {
        xTaskCreatePinnedToCore(
            HrdwrReader::readBttryVoltageTask, // Task function
            "readBttryVoltageTask", // Task name
            1024, // Stack size
            NULL, // Parameters
            readBttryVoltageTaskPriority, // Priority
            NULL, // Task handle
            1 // Core ID
        );
    }
}

/*
*   Tasker public function definitions
*/

void Tasker::setupTasks( TaskHandle_t mainTaskHandle )
{
    vTaskPrioritySet( mainTaskHandle, mainTaskPriority );

    /*
    createPlaySongTask();
    vTaskSuspend( musicTaskHandle );

    createMusicCtrlTask();
    */

    createBttryReadTask();
}

TaskHandle_t Tasker::getMusicTaskHandle()
{
    return musicTaskHandle;
}
