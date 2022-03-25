#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64, SCNu64 */
#include <assert.h>
#include <pthread.h>
#include <string.h>
#include <orca/discord.h> /* Discord Lib */
#include "commands/def.h" /* Commands */

void on_ready(struct discord *client)   {
  const struct discord_user *bot = discord_get_self(client);

    log_info("[BOT] succesfully connected to Discord as %s#%s!", bot->username, bot->discriminator);

    discord_set_presence(client, &(struct discord_presence_status){.activities = (struct discord_activity *[])  { 
        &(struct discord_activity){
            //  .name = "&help",
                .type = DISCORD_ACTIVITY_GAME,
        },
        NULL // END OF ACTIVITY ARRAY
    },
        .status = "dnd",
        .afk = false,
        .since = discord_timestamp(client),
    });

}

int main(int argc, char const *argv[])  {
    const char *config_file;
    if(argc > 1)    {
        config_file = argv[1];
    }else   {
        config_file = "./config.json";
    }

    orca_global_init();
    struct discord *client = discord_config_init(config_file);
    assert(NULL != client && "Could not initialize client");

    discord_remove_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES);
    discord_set_on_ready(client, &on_ready);
    discord_set_prefix(client, "&");

    /*bot commands*/


    /*bot commands*/

    printf("\n\n[BOT] press enter to start\n");
    fgetc(stdin);

    pthread_t tid;

    discord_run(client)
    discord_cleanup(client);    
    orca_global_cleanup();
}