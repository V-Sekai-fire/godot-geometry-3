def can_build(env, platform):    
    return env["target"] == "editor" and not env["disable_3d"]


def configure(env):
    pass
