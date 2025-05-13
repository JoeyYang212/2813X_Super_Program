#include "selector/Selector.hpp"
#include "liblvgl/lvgl.h"
#include "liblvgl/widgets/lv_btnmatrix.h"
#include "pros/rtos.hpp"
#include "setup.hpp"
#include "pros/screen.hpp"

extern bool team;
namespace Teamselector {
    pros::Mutex auton_mtx;

    lv_obj_t* redBtnm;
    lv_obj_t* blueBtnm;
    lv_obj_t* skillsBtnm;

    // Autonomous列表
    int auton;
    const char* btnmMap[11] = {"","","","","","","","","","",""};
    const char* skillsMap[] = {"Skills", ""};

    void render(){
        lv_btnmatrix_clear_btn_ctrl_all(redBtnm, LV_BTNMATRIX_CTRL_CHECKED);
        lv_btnmatrix_clear_btn_ctrl_all(blueBtnm, LV_BTNMATRIX_CTRL_CHECKED);
        lv_btnmatrix_clear_btn_ctrl_all(skillsBtnm, LV_BTNMATRIX_CTRL_CHECKED);
        if(auton == 0){
            lv_btnmatrix_set_btn_ctrl(skillsBtnm, 0, LV_BTNMATRIX_CTRL_CHECKED);
        }
        else if(auton > 0){
            lv_btnmatrix_set_btn_ctrl(redBtnm, auton - 1, LV_BTNMATRIX_CTRL_CHECKED);
        }
        else if (auton < 0) {
            lv_btnmatrix_set_btn_ctrl(blueBtnm, -auton - 1, LV_BTNMATRIX_CTRL_CHECKED);        
        }
    }

    void init( int default_auton, const char** autons){
        
    }

}