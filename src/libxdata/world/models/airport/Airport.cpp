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
#include <algorithm>
#include "Airport.h"
#include "src/libxdata/world/models/navaids/Fix.h"

namespace xdata {

Airport::Airport(const std::string& airportId):
    id(airportId)
{
}

void Airport::setName(const std::string& name) {
    this->name = name;
}

void Airport::setElevation(int elevation) {
    this->elevation = elevation;
}

void Airport::setLocation(const Location& loc) {
    this->location = loc;
}

void Airport::setRegion(std::shared_ptr<Region> region) {
    this->region = region;
}

void Airport::addATCFrequency(ATCFrequency which, const Frequency &frq) {
    atcFrequencies[which].push_back(frq);
}

void Airport::addRunway(const Runway& rwy) {
    runways.insert(std::make_pair(rwy.getName(), rwy));
}

void Airport::setCurrentMetar(const std::string& timestamp, const std::string& metar) {
    metarTimestamp = timestamp;
    metarString = metar;
}

const std::string& Airport::getID() const {
    return id;
}

const std::string& Airport::getName() const {
    return name;
}

const std::vector<Frequency> &Airport::getATCFrequencies(ATCFrequency type) {
    return atcFrequencies[type];
}

void Airport::attachILSData(const std::string& rwyName, std::weak_ptr<Fix> ils) {
    auto rwy = runways.find(rwyName);
    if (rwy == runways.end()) {
        throw std::runtime_error("Unknown runway: " + rwyName);
    }
    rwy->second.attachILSData(ils);
}

const Runway &Airport::getRunwayByName(const std::string& rw) const {
    auto rwy = runways.find(rw);
    if (rwy == runways.end()) {
        throw std::runtime_error("Unknown runway: " + rw);
    }
    return rwy->second;
}

void Airport::forEachRunway(std::function<void(const Runway&)> f) {
    for (auto &rwy: runways) {
        f(rwy.second);
    }
}

void Airport::addSID(const SID& sid) {
    sids.insert(std::make_pair(sid.getID(), sid));
}

void Airport::addSTAR(const STAR& star) {
    stars.insert(std::make_pair(star.getID(), star));
}

void Airport::addApproach(const Approach& approach) {
    approaches.insert(std::make_pair(approach.getID(), approach));
}

std::vector<std::weak_ptr<Fix>> Airport::getArrivalFixes() const {
    std::vector<std::weak_ptr<Fix>> res;

    for (auto &it: stars) {
        auto fix = it.second.getStartFix();
        if (!containsFix(res, fix)) {
            res.push_back(fix);
        }
    }

    for (auto &it: approaches) {
        auto fix = it.second.getStartFix();
        if (!containsFix(res, fix)) {
            res.push_back(fix);
        }
    }

    return res;
}

std::vector<std::weak_ptr<Fix>> Airport::getDepartureFixes() const {
    std::vector<std::weak_ptr<Fix>> res;

    for (auto &it: sids) {
        auto fix = it.second.getDestionationFix();
        if (!containsFix(res, fix)) {
            res.push_back(fix);
        }
    }

    return res;
}

const std::string& Airport::getMetarTimestamp() const {
    return metarTimestamp;
}

const std::string& Airport::getMetarString() const {
    return metarString;
}

bool Airport::containsFix(std::vector<std::weak_ptr<Fix>> &fixes, std::weak_ptr<Fix> fix) const {
    for (auto &it: fixes) {
        if (it.lock().get() == fix.lock().get()) {
            return true;
        }
    }
    return false;
}

} /* namespace xdata */
