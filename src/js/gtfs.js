'use strict';

// FeedMessage ========================================

var FeedMessage = exports.FeedMessage = {};

FeedMessage.read = function (pbf, end) {
    return pbf.readFields(FeedMessage._readField, {entity: []}, end);
};
FeedMessage._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.header = FeedHeader.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 2) obj.entity.push(FeedEntity.read(pbf, pbf.readVarint() + pbf.pos));
};

// FeedHeader ========================================

var FeedHeader = exports.FeedHeader = {};

FeedHeader.read = function (pbf, end) {
    return pbf.readFields(FeedHeader._readField, {incrementality: "FULL_DATASET"}, end);
};
FeedHeader._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.gtfs_realtime_version = pbf.readString();
    else if (tag === 2) obj.incrementality = pbf.readVarint();
    else if (tag === 3) obj.timestamp = pbf.readVarint();
};

FeedHeader.Incrementality = {
    "FULL_DATASET": 0,
    "DIFFERENTIAL": 1
};

// FeedEntity ========================================

var FeedEntity = exports.FeedEntity = {};

FeedEntity.read = function (pbf, end) {
    return pbf.readFields(FeedEntity._readField, {}, end);
};
FeedEntity._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.id = pbf.readString();
    else if (tag === 2) obj.is_deleted = pbf.readBoolean();
    else if (tag === 3) obj.trip_update = TripUpdate.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 4) obj.vehicle = VehiclePosition.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 5) obj.alert = Alert.read(pbf, pbf.readVarint() + pbf.pos);
};

// TripUpdate ========================================

var TripUpdate = exports.TripUpdate = {};

TripUpdate.read = function (pbf, end) {
    return pbf.readFields(TripUpdate._readField, {stop_time_update: []}, end);
};
TripUpdate._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.trip = TripDescriptor.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 3) obj.vehicle = VehicleDescriptor.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 2) obj.stop_time_update.push(TripUpdate.StopTimeUpdate.read(pbf, pbf.readVarint() + pbf.pos));
    else if (tag === 4) obj.timestamp = pbf.readVarint();
};

// TripUpdate.StopTimeEvent ========================================

TripUpdate.StopTimeEvent = {};

TripUpdate.StopTimeEvent.read = function (pbf, end) {
    return pbf.readFields(TripUpdate.StopTimeEvent._readField, {}, end);
};
TripUpdate.StopTimeEvent._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.delay = pbf.readVarint();
    else if (tag === 2) obj.time = pbf.readVarint();
    else if (tag === 3) obj.uncertainty = pbf.readVarint();
};

// TripUpdate.StopTimeUpdate ========================================

TripUpdate.StopTimeUpdate = {};

TripUpdate.StopTimeUpdate.read = function (pbf, end) {
    return pbf.readFields(TripUpdate.StopTimeUpdate._readField, {schedule_relationship: "SCHEDULED"}, end);
};
TripUpdate.StopTimeUpdate._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.stop_sequence = pbf.readVarint();
    else if (tag === 4) obj.stop_id = pbf.readString();
    else if (tag === 2) obj.arrival = TripUpdate.StopTimeEvent.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 3) obj.departure = TripUpdate.StopTimeEvent.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 5) obj.schedule_relationship = pbf.readVarint();
};

TripUpdate.StopTimeUpdate.ScheduleRelationship = {
    "SCHEDULED": 0,
    "SKIPPED": 1,
    "NO_DATA": 2
};

// VehiclePosition ========================================

var VehiclePosition = exports.VehiclePosition = {};

VehiclePosition.read = function (pbf, end) {
    return pbf.readFields(VehiclePosition._readField, {current_status: "IN_TRANSIT_TO"}, end);
};
VehiclePosition._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.trip = TripDescriptor.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 8) obj.vehicle = VehicleDescriptor.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 2) obj.position = Position.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 3) obj.current_stop_sequence = pbf.readVarint();
    else if (tag === 7) obj.stop_id = pbf.readString();
    else if (tag === 4) obj.current_status = pbf.readVarint();
    else if (tag === 5) obj.timestamp = pbf.readVarint();
    else if (tag === 6) obj.congestion_level = pbf.readVarint();
    else if (tag === 9) obj.occupancy_status = pbf.readVarint();
};

VehiclePosition.VehicleStopStatus = {
    "INCOMING_AT": 0,
    "STOPPED_AT": 1,
    "IN_TRANSIT_TO": 2
};

VehiclePosition.CongestionLevel = {
    "UNKNOWN_CONGESTION_LEVEL": 0,
    "RUNNING_SMOOTHLY": 1,
    "STOP_AND_GO": 2,
    "CONGESTION": 3,
    "SEVERE_CONGESTION": 4
};

VehiclePosition.OccupancyStatus = {
    "EMPTY": 0,
    "MANY_SEATS_AVAILABLE": 1,
    "FEW_SEATS_AVAILABLE": 2,
    "STANDING_ROOM_ONLY": 3,
    "CRUSHED_STANDING_ROOM_ONLY": 4,
    "FULL": 5,
    "NOT_ACCEPTING_PASSENGERS": 6
};

// Alert ========================================

var Alert = exports.Alert = {};

Alert.read = function (pbf, end) {
    return pbf.readFields(Alert._readField, {active_period: [], informed_entity: [], cause: "UNKNOWN_CAUSE", effect: "UNKNOWN_EFFECT"}, end);
};
Alert._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.active_period.push(TimeRange.read(pbf, pbf.readVarint() + pbf.pos));
    else if (tag === 5) obj.informed_entity.push(EntitySelector.read(pbf, pbf.readVarint() + pbf.pos));
    else if (tag === 6) obj.cause = pbf.readVarint();
    else if (tag === 7) obj.effect = pbf.readVarint();
    else if (tag === 8) obj.url = TranslatedString.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 10) obj.header_text = TranslatedString.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 11) obj.description_text = TranslatedString.read(pbf, pbf.readVarint() + pbf.pos);
};

Alert.Cause = {
    "UNKNOWN_CAUSE": 1,
    "OTHER_CAUSE": 2,
    "TECHNICAL_PROBLEM": 3,
    "STRIKE": 4,
    "DEMONSTRATION": 5,
    "ACCIDENT": 6,
    "HOLIDAY": 7,
    "WEATHER": 8,
    "MAINTENANCE": 9,
    "CONSTRUCTION": 10,
    "POLICE_ACTIVITY": 11,
    "MEDICAL_EMERGENCY": 12
};

Alert.Effect = {
    "NO_SERVICE": 1,
    "REDUCED_SERVICE": 2,
    "SIGNIFICANT_DELAYS": 3,
    "DETOUR": 4,
    "ADDITIONAL_SERVICE": 5,
    "MODIFIED_SERVICE": 6,
    "OTHER_EFFECT": 7,
    "UNKNOWN_EFFECT": 8,
    "STOP_MOVED": 9
};

// TimeRange ========================================

var TimeRange = exports.TimeRange = {};

TimeRange.read = function (pbf, end) {
    return pbf.readFields(TimeRange._readField, {}, end);
};
TimeRange._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.start = pbf.readVarint();
    else if (tag === 2) obj.end = pbf.readVarint();
};

// Position ========================================

var Position = exports.Position = {};

Position.read = function (pbf, end) {
    return pbf.readFields(Position._readField, {}, end);
};
Position._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.latitude = pbf.readFloat();
    else if (tag === 2) obj.longitude = pbf.readFloat();
    else if (tag === 3) obj.bearing = pbf.readFloat();
    else if (tag === 4) obj.odometer = pbf.readDouble();
    else if (tag === 5) obj.speed = pbf.readFloat();
};

// TripDescriptor ========================================

var TripDescriptor = exports.TripDescriptor = {};

TripDescriptor.read = function (pbf, end) {
    return pbf.readFields(TripDescriptor._readField, {}, end);
};
TripDescriptor._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.trip_id = pbf.readString();
    else if (tag === 5) obj.route_id = pbf.readString();
    else if (tag === 2) obj.start_time = pbf.readString();
    else if (tag === 3) obj.start_date = pbf.readString();
    else if (tag === 4) obj.schedule_relationship = pbf.readVarint();
};

TripDescriptor.ScheduleRelationship = {
    "SCHEDULED": 0,
    "ADDED": 1,
    "UNSCHEDULED": 2,
    "CANCELED": 3,
    "REPLACEMENT": 5
};

// VehicleDescriptor ========================================

var VehicleDescriptor = exports.VehicleDescriptor = {};

VehicleDescriptor.read = function (pbf, end) {
    return pbf.readFields(VehicleDescriptor._readField, {}, end);
};
VehicleDescriptor._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.id = pbf.readString();
    else if (tag === 2) obj.label = pbf.readString();
    else if (tag === 3) obj.license_plate = pbf.readString();
};

// EntitySelector ========================================

var EntitySelector = exports.EntitySelector = {};

EntitySelector.read = function (pbf, end) {
    return pbf.readFields(EntitySelector._readField, {}, end);
};
EntitySelector._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.agency_id = pbf.readString();
    else if (tag === 2) obj.route_id = pbf.readString();
    else if (tag === 3) obj.route_type = pbf.readVarint();
    else if (tag === 4) obj.trip = TripDescriptor.read(pbf, pbf.readVarint() + pbf.pos);
    else if (tag === 5) obj.stop_id = pbf.readString();
};

// TranslatedString ========================================

var TranslatedString = exports.TranslatedString = {};

TranslatedString.read = function (pbf, end) {
    return pbf.readFields(TranslatedString._readField, {translation: []}, end);
};
TranslatedString._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.translation.push(TranslatedString.Translation.read(pbf, pbf.readVarint() + pbf.pos));
};

// TranslatedString.Translation ========================================

TranslatedString.Translation = {};

TranslatedString.Translation.read = function (pbf, end) {
    return pbf.readFields(TranslatedString.Translation._readField, {}, end);
};
TranslatedString.Translation._readField = function (tag, obj, pbf) {
    if (tag === 1) obj.text = pbf.readString();
    else if (tag === 2) obj.language = pbf.readString();
};
