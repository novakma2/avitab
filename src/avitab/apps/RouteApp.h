/*
 *   AviTab - Aviator's Virtual Tablet
 *   Copyright (C) 2018 Folke Will <folko@solhost.org>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Affero General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Affero General Public License for more details.
 *
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef SRC_AVITAB_APPS_ROUTEAPP_H_
#define SRC_AVITAB_APPS_ROUTEAPP_H_

#include <memory>
#include "App.h"
#include "src/gui_toolkit/widgets/TabGroup.h"
#include "src/gui_toolkit/widgets/Page.h"
#include "src/gui_toolkit/widgets/TextArea.h"
#include "src/gui_toolkit/widgets/Keyboard.h"
#include "src/gui_toolkit/widgets/Label.h"

namespace avitab {

class RouteApp: public App {
public:
    RouteApp(FuncsPtr appFuncs);
private:
    std::shared_ptr<TabGroup> tabs;
    std::shared_ptr<Page> routePage;
    std::shared_ptr<Keyboard> keys;
    std::shared_ptr<Label> departureLabel;
    std::shared_ptr<TextArea> departureField;
    std::shared_ptr<Label> arrivalLabel;
    std::shared_ptr<TextArea> arrivalField;
    std::shared_ptr<Label> errorLabel;
    bool inDeparture = true;

    void resetLayout();
    void resetContent();
    void onNextClicked();
    bool createRoute();
};

} /* namespace avitab */

#endif /* SRC_AVITAB_APPS_ROUTEAPP_H_ */
