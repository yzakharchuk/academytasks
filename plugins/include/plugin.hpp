#pragma once


namespace pe {
struct plugin {
    plugin() = default;
    virtual ~plugin() = default;

    virtual void execute() const = 0;
    virtual void release() = 0;
};

} // namespace pe